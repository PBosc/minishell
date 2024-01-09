/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:29:13 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/09 11:23:15 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parsing.h"

char	*expanded_heredoc(char *str)
{
	int		i;
	char	*name;
	char	*env_value;

	i = 0;
	name = get_name(str, &i);
	if (!name)
		return (str);
	if (!ft_strlen(name))
	{
		return (ft_strdup(""));
	}
	env_value = getenv(name);
	if (!env_value && !str[i])
		return (NULL);
	if (!env_value)
		return (ft_strjoin(ft_substr(str, 0, ft_strchri(str, '$')),
				expanded_heredoc(str + i)));
	return (ft_strjoin(ft_strjoin(ft_substr(str, 0, ft_strchri(str, '$')),
				env_value), expanded_heredoc(str + i)));
}

int	read_here_doc(t_hered **here_doc, t_exec *data)
{
	char	*line;

	while (1)
	{
		line = ft_strjoin(readline("> "), "\n");
		if (!line)
			return (perror("malloc"), 0);
		line = expanded_heredoc(line);
		if (is_limit(line, data->limiter))
			return (free(line), 1);
		if (!ft_lstpush_back(here_doc, line))
			return (free(line), perror("malloc list"), 0);
		free(line);
	}
	return (0);
}

int	write_here_doc(t_hered *here_doc, t_exec *data)
{
	t_hered	*node;

	node = here_doc;
	while (node && node->line)
	{
		write(data->pipe[1], node->line, ft_strlen(node->line));
		node = node->next;
	}
	return (1);
}

void	child_heredoc(t_hered *heredoc, t_exec *data)
{
	write_here_doc(heredoc, data);
	free_heredoc(heredoc);
	close(data->pipe[0]);
	close(data->pipe[1]);
	exit(EXIT_SUCCESS);
}

int	init_heredoc(t_exec *data)
{
	t_hered		*heredoc;
	pid_t		child_pid;
	int			ret;

	if (pipe(data->pipe) == -1)
		return (perror("pipe"), 0);
	heredoc = NULL;
	ret = read_here_doc(&heredoc, data);
	if (ret == 0)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		child_heredoc(heredoc, data);
	close(data->pipe[1]);
	free_heredoc(heredoc);
	data->prev_pipe = data->pipe[0];
	return (1);
}
