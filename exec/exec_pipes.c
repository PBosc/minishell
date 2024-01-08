/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:37:51 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/08 21:26:51 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void print_here_doc(t_hered *heredoc)
{
	while (heredoc)
	{
		ft_putstr_fd(heredoc->line, STDOUT_FILENO);
		heredoc = heredoc->next;
	}
}

int	child_pipes(t_exec *data, int is_end)
{
	if (data->fd_in != STDIN_FILENO && data->fd_in != REDIR_HEREDOC)
		dup2(data->fd_in, STDIN_FILENO);
	else if (data->prev_pipe != -1)
		dup2(data->prev_pipe, STDIN_FILENO);
	if (is_end)
	{
		if (data->fd_out != STDOUT_FILENO)
			dup2(data->fd_out, STDOUT_FILENO);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	close(data->pipe[0]);
	return (EXIT_SUCCESS);
}

void	exec_pipe(t_node_ast *node, t_exec *data, int is_end, t_minishell *minishell)
{
	get_redirs(node->redirs, data);
	if (data->fd_in == REDIR_HEREDOC)
		init_heredoc(data);
	if (!is_builtin(node->args[0]))
		node->args[0] = get_valid_path(get_path(data->env), node->args[0]);
	if (node->args[0] == NULL || (!is_builtin(node->args[0]) && access(node->args[0], F_OK | X_OK) == -1))
	{
		g_status = 127;
		if (!node->args[0])
			return ;
		dprintf(2, "minishell: %s: %s\n", node->args[0], strerror(errno));
		close(data->pipe[0]);
		close(data->pipe[1]);
		return ;
	}
	if (pipe(data->pipe) == -1)
		return ;
	data->pid = fork();
	if (data->pid == -1)
		return ;
	if (data->pid == 0)
	{
		child_pipes(data, is_end);
		if (is_builtin(node->args[0]))
			exec_builtin(node->args, minishell);
		else
			execve(node->args[0], node->args, tab_env(data->env));
		exit(data->ret_value);
	}
	else
	{
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		data->prev_pipe = data->pipe[0];
		close(data->pipe[1]);
	}
}

void	exec_pipeline(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (node->left_child->type == T_PIPE)
		exec_pipeline(node->left_child, data, minishell);
	if (node->left_child->type == T_CMD)
		exec_pipe(node->left_child, data, 0, minishell);
	if (node->right_child->type == T_CMD)
		exec_pipe(node->right_child, data, 0, minishell);
}

int	exec_master_pipe(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (node->left_child->type == T_CMD)
	{
		exec_pipe(node->left_child, data, 0, minishell);
		exec_pipe(node->right_child, data, 1, minishell);
		g_status = wait_commands(data);
		close(data->pipe[0]);
		close(data->pipe[1]);
		close(data->prev_pipe);
		return (g_status);
	}
	else if (node->left_child->type == T_PIPE)
	{
		exec_pipeline(node->left_child, data, minishell);
		exec_pipe(node->right_child, data, 1, minishell);
		g_status = wait_commands(data);
		close(data->pipe[0]);
		close(data->pipe[1]);
		close(data->prev_pipe);
		return (g_status);
	}
	else
	{
		data->is_pipe = 1;
		exec(node->left_child, data, minishell);
		exec_pipe(node->right_child, data, 1, minishell);
		data->is_pipe = 0;
		g_status = wait_commands(data);
		close(data->pipe[0]);
		close(data->pipe[1]);
		close(data->prev_pipe);
		return (g_status);
	}
}
