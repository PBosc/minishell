/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:13:00 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 21:32:01 by pibosc           ###   ########.fr       */
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
			ft_dprintf(STDERR_FILENO, "\n");
		else if (WTERMSIG(exec->status) == 3)
			ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
		if (WIFEXITED(exec->status))
			g_status = WEXITSTATUS(exec->status);
		else
			g_status = 128 + WTERMSIG(exec->status);
	}
	return (g_status);
}

void	handle_heredoc(t_exec *data, t_minishell *minishell)
{
	t_hered	*heredoc;

	heredoc = NULL;
	read_here_doc(&heredoc, data, minishell);
	write_here_doc(heredoc, data);
	dup2(data->pipe[0], STDIN_FILENO);
	if (data->pipe[0] != -1)
		ft_close(data->pipe[0]);
}

void	child_fds(t_exec *data, t_minishell *minishell)
{
	if (data->fd_in != STDIN_FILENO && data->fd_in != REDIR_HEREDOC)
	{
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(data->fd_in);
	}
	if (data->fd_in == REDIR_HEREDOC)
		handle_heredoc(data, minishell);
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		ft_close(data->fd_out);
	}
	if (data->is_pipe && data->fd_out == STDOUT_FILENO)
	{
		dup2(data->pipe[1], STDOUT_FILENO);
		if (data->pipe[0] != -1)
			ft_close(data->pipe[0]);
	}
}

static inline void	sig_fork(t_exec *data)
{
	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_sig_handler);
	data->pid = fork();
}

int	exec_cmd(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	char	**env_tab;

	if (precheck(node, data, minishell))
		return (EXIT_FAILURE);
	sig_fork(data);
	if (data->pid == -1)
		return (EXIT_FAILURE);
	if (data->pid == 0)
	{
		child_fds(data, minishell);
		if (!data->is_pipe)
			ft_close(data->pipe[1]);
		env_tab = tab_env(data->env);
		execve(node->args[0], node->args, env_tab);
		(free_tab_2d(env_tab), exit(data->ret_value));
	}
	else
	{
		if (!data->is_pipe)
			ft_close(data->pipe[1]);
		else
			data->fd_in = data->pipe[0];
		data->fd_out = STDOUT_FILENO;
		return (g_status);
	}
}
