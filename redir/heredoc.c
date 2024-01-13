/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:29:13 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 23:36:59 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parsing.h"

int	read_here_doc(t_hered **here_doc, t_exec *data, t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		garbage_collector(minishell, here_doc, 0);
		line = readline("> ");
		if (!line)
			return (ft_dprintf(2, "minishell: warning: here-document delimited by end-of-file \
(wanted `%s`)\n", data->limiter), 0);
		if (!ft_strcmp(line, data->limiter))
			return (free(line), 1);
		line = ft_strjoin(line, "\n");
		if (!minishell)
			line = expanded_heredoc(line, minishell);
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

void	child_heredoc(t_hered *heredoc, t_exec *data,
t_minishell *ms, int ignore_fork)
{
	if (!read_here_doc(&heredoc, data, ms) && !ignore_fork)
		exit(g_status);
	write_here_doc(heredoc, data);
	free_heredoc(heredoc);
	ft_close(data->pipe[0]);
	ft_close(data->pipe[1]);
	if (!ignore_fork)
	{
		clear_ast(&ms->ast);
		clear_env(&ms->env);
		free(ms);
		exit(EXIT_SUCCESS);
	}
}

int	init_heredoc(t_exec *data, t_minishell *minishell, int ignore_fork)
{
	t_hered		*heredoc;
	pid_t		child_pid;

	child_pid = -1;
	if (pipe(data->pipe) == -1)
		return (perror("pipe"), 0);
	heredoc = NULL;
	if (!ignore_fork)
		child_pid = fork();
	if (child_pid == -1 && !ignore_fork)
		return (0);
	if (child_pid == 0 || ignore_fork)
		child_heredoc(heredoc, data, minishell, ignore_fork);
	else if (!ignore_fork)
		g_status = wait_commands(data);
	ft_close(data->pipe[1]);
	free_heredoc(heredoc);
	data->prev_pipe = data->pipe[0];
	return (1);
}

void	close_pipes(t_exec *data)
{
	if (data->pipe[0] != -1)
		ft_close(data->pipe[0]);
	if (data->pipe[1] != -1)
		ft_close(data->pipe[1]);
	if (data->fd_in != -1 && data->fd_in != 0 && data->fd_in != -42)
		ft_close(data->fd_in);
	if (data->fd_out != -1 && data->fd_out != 1)
		ft_close(data->fd_out);
}
