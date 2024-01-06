/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:13:00 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/06 23:49:01 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	wait_commands(t_exec *exec)
{
	while (1)
	{
		dprintf(STDERR_FILENO, "wait\n");
		exec->wpid = wait(&exec->status);
		dprintf(STDERR_FILENO, "wait2\n");
		if (exec->wpid == -1)
			break ;
		if (exec->wpid != exec->pid || exec->ret_value != EXIT_SUCCESS)
			continue ;
		if (WTERMSIG(exec->status) == 2)
			dprintf(STDERR_FILENO, "\n");
		else if (WTERMSIG(exec->status) == 3)
			dprintf(STDERR_FILENO, "Quit (core dumped)\n");
		if (WIFEXITED(exec->status))
			exec->ret_value = WEXITSTATUS(exec->status);
		else
			exec->ret_value = 128 + WTERMSIG(exec->status);
	}
	return (exec->ret_value);
}

void	child_fds(t_exec *data)
{
	t_hered	*heredoc;

	heredoc = NULL;
	if (data->fd_in != STDIN_FILENO && data->fd_in != REDIR_HEREDOC)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (data->fd_in == REDIR_HEREDOC)
	{
		read_here_doc(&heredoc, data);
		write_here_doc(heredoc, data);
		dup2(data->pipe[0], STDIN_FILENO);
		close(data->pipe[0]);
	}
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	if (data->is_pipe && data->fd_out == STDOUT_FILENO)
	{
		dup2(data->pipe[1], STDOUT_FILENO);
		if (data->pipe[0] != -1)
			close(data->pipe[0]);
	}
}

int	exec_cmd(t_node_ast *node, t_exec *data)
{
	if (pipe(data->pipe) == -1)
		return (EXIT_FAILURE);
	node->args[0] = get_valid_path(get_path(data->env), node->args[0]);
	data->pid = fork();
	if (data->pid == -1)
		return (EXIT_FAILURE);
	if (data->pid == 0)
	{
		get_redirs(node->redirs, data);
		child_fds(data);
		if (!data->is_pipe)
			close(data->pipe[1]);
		execve(node->args[0], node->args, data->env);
		exit(data->ret_value);
	}
	else
	{
		if (!data->is_pipe)
			close(data->pipe[1]);
		data->fd_in = data->pipe[0];
		data->fd_out = STDOUT_FILENO;
		return (g_status);
	}
}
