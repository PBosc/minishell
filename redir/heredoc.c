/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:29:13 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/08 19:46:58 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parsing.h"

static int	is_limit(char *line, char *limiter)
{
	int	length;

	length = ft_strlen(limiter);
	if (line[0] == '\n')
		return (0);
	return (ft_strncmp(line, limiter, length) == 0
		&& (line[length] == '\n'));
}

void	free_heredoc(t_hered *here_doc)
{
	t_hered	*tmp;

	while (here_doc)
	{
		tmp = here_doc;
		here_doc = here_doc->next;
		free(tmp->line);
		free(tmp);
	}
}

t_hered	*ft_hered_last(t_hered *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static int	ft_lstpush_back(t_hered **lst, char *line)
{
	t_hered	*new;

	new = malloc(sizeof(t_hered));
	if (!new)
		return (0);
	new->line = ft_strdup(line);
	new->next = NULL;
	if (lst)
	{
		if (*lst)
			ft_hered_last(*lst)->next = new;
		else
			*lst = new;
	}
	return (1);
}

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
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (get_next_line(-42), perror("malloc"), 0);
		line = expanded_heredoc(line);
		if (is_limit(line, data->limiter))
			return (get_next_line(-42), free(line), 1);
		if (!ft_lstpush_back(here_doc, line))
			return (free(line),
				get_next_line(-42), perror("malloc list"), 0);
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
	// free(data->limiter);
	if (ret == 0)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		child_heredoc(heredoc, data);
	close(data->pipe[1]);
	data->prev_pipe = data->pipe[0];
	return (1);
}
