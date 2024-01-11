/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:37:51 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/11 02:44:49 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_pipe(t_node_ast *node, t_exec *data,
	int is_end, t_minishell *minishell)
{	
	if (pipe_precheck(node, data, minishell))
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
		close_pipes(data);
		exit(data->ret_value);
	}
	else
	{
		if (data->prev_pipe != -1)
			close(data->prev_pipe);
		data->prev_pipe = data->pipe[0];
		close(data->pipe[1]);
		close(data->fd_out);
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

int	exec_2pipes(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	exec_pipe(node->left_child, data, 0, minishell);
	exec_pipe(node->right_child, data, 1, minishell);
	g_status = wait_commands(data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->prev_pipe);
	return (g_status);
}

int	exec_more_pipes(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	exec_pipeline(node->left_child, data, minishell);
	exec_pipe(node->right_child, data, 1, minishell);
	g_status = wait_commands(data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->prev_pipe);
	return (g_status);
}

int	exec_master_pipe(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (node->left_child->type == T_CMD)
		return (exec_2pipes(node, data, minishell));
	else if (node->left_child->type == T_PIPE)
		return (exec_more_pipes(node, data, minishell));
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
