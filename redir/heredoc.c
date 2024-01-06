/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:29:13 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/06 21:05:16 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parsing.h"

static int	is_limit(char *line, char *limiter)
{
	int	length;

	length = ft_strlen(line) - 1;
	if (line[0] == '\n')
		return (0);
	return (ft_strncmp(line, limiter, length) == 0
		&& (line[length] == '\n'));
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