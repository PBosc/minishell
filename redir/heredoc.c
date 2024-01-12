/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:29:13 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/12 03:56:07 by pibosc           ###   ########.fr       */
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

void	child_heredoc(t_hered *heredoc, t_exec *data, t_minishell *ms)
{
	write_here_doc(heredoc, data);
	free_heredoc(heredoc);
	close(data->pipe[0]);
	close(data->pipe[1]);
	clear_ast(&ms->ast);
	clear_env(&ms->env);
	free(ms);
	exit(EXIT_SUCCESS);
}

int	init_heredoc(t_exec *data, t_minishell *minishell, int ignore_fork)
{
	t_hered		*heredoc;
	pid_t		child_pid;
	int			ret;

	child_pid = -1;
	if (pipe(data->pipe) == -1)
		return (perror("pipe"), 0);
	heredoc = NULL;
	ret = read_here_doc(&heredoc, data, minishell);
	if (ret == 0)
		return (0);
	if (!ignore_fork)
		child_pid = fork();
	else
		free_heredoc(heredoc);
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		child_heredoc(heredoc, data, minishell);
	close(data->pipe[1]);
	free_heredoc(heredoc);
	data->prev_pipe = data->pipe[0];
	return (1);
}

void	close_pipes(t_exec *data)
{
	if (data->pipe[0] != -1)
		close(data->pipe[0]);
	if (data->pipe[1] != -1)
		close(data->pipe[1]);
	if (data->fd_in != -1 && data->fd_in != 0 && data->fd_in != -42)
		close(data->fd_in);
	if (data->fd_out != -1 && data->fd_out != 1)
		close(data->fd_out);
}
