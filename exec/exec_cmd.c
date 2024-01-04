/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:13:00 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/01 17:15:30 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	wait_commands(t_exec *exec)
{
	while (1)
	{
		exec->wpid = wait(&exec->status);
		if (exec->wpid == -1)
			break ;
		if (exec->wpid != exec->pid || exec->ret_value != EXIT_SUCCESS)
			continue ;
		if (WTERMSIG(exec->status) == 2)
			ft_dprintf(STDERR_FILENO, "\n");
		else if (WTERMSIG(exec->status) == 3)
			ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
		if (WIFEXITED(exec->status))
			exec->ret_value = WEXITSTATUS(exec->status);
		else
			exec->ret_value = 128 + WTERMSIG(exec->status);
	}
	return (exec->ret_value);
}

void child_pipes(t_exec *data)
{
	if (data->fd_in != STDIN_FILENO && data->fd_in != PIPE)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	else if (data->fd_in == PIPE)
		dup2(data->prev_pipe, STDIN_FILENO);
	if (data->fd_out != STDOUT_FILENO && data->fd_out != PIPE)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	else if (data->fd_out == PIPE)
		dup2(data->pipe[1], STDOUT_FILENO);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	if (data->pipe[0] != -1)
		close(data->pipe[0]);
}

int   exec_cmd(t_node_ast *node, t_exec *data)
{
	if (pipe(data->pipe) == -1)
		return (EXIT_FAILURE);
	data->pid = fork();
	if (data->pid == -1)
		return (EXIT_FAILURE);
	if (data->pid == 0)
	{
		child_pipes(data);
		//todo: get command path, args and execve
		exit(data->ret_value);
	}
	else
	{
		close(data->pipe[1]);
		data->fd_in = data->pipe[0];
		data->fd_out = STDOUT_FILENO;
		return (wait_commands(data));
	}
}
