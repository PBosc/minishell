/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:13:00 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/08 21:34:24 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	wait_commands(t_exec *exec)
{
	while (1)
	{
		exec->wpid = wait(&exec->status);
		if (exec->wpid == -1)
			break ;
		if (exec->wpid != exec->pid)
			continue ;
		if (WTERMSIG(exec->status) == 2)
			dprintf(STDERR_FILENO, "\n");
		else if (WTERMSIG(exec->status) == 3)
			dprintf(STDERR_FILENO, "Quit (core dumped)\n");
		if (WIFEXITED(exec->status))
		{
			g_status = WEXITSTATUS(exec->status);
			printf("exit status: %d\n", g_status);
		}
		else
			g_status = 128 + WTERMSIG(exec->status);
	}
	return (g_status);
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

int	exec_cmd(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (data->is_pipe)
		return (exec_pipe(node, data, 0, minishell), 0);
	if (pipe(data->pipe) == -1)
		return (EXIT_FAILURE);
	if (!is_builtin(node->args[0]))
		node->args[0] = get_valid_path(get_path(data->env), node->args[0]);
	if (node->args[0] == NULL || (!is_builtin(node->args[0]) && access(node->args[0], F_OK | X_OK) == -1))
	{
		g_status = 127;
		if (!node->args[0])
			return (g_status);
		dprintf(2, "minishell: %s: %s\n", node->args[0], strerror(errno));
		return (g_status);
	}
	if (is_builtin(node->args[0]))
		return (exec_builtin(node->args, minishell), 0);
	data->pid = fork();
	if (data->pid == -1)
		return (EXIT_FAILURE);
	if (data->pid == 0)
	{
		get_redirs(node->redirs, data);
		child_fds(data);
		if (!data->is_pipe)
			close(data->pipe[1]);
		execve(node->args[0], node->args, tab_env(data->env));
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
