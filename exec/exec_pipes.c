/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:37:51 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/05 01:06:35 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


int	child_pipes(t_exec *data)
{
	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	else if (data->prev_pipe != -1)
		dup2(data->prev_pipe, STDIN_FILENO);
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	close(data->pipe[0]);
	return (EXIT_SUCCESS);
}

int    exec_pipe(t_node_ast *node, t_exec *data)
{
	if (pipe(data->pipe) == -1)
		return (EXIT_FAILURE);
	node->args[0] = get_valid_path(get_path(data->env), node->args[0]);
	data->pid = fork();
	if (data->pid == -1)
		return (EXIT_FAILURE);
	if (data->pid == 0)
	{
		child_pipes(data);
		execve(node->args[0], node->args, data->env);
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

int exec_pipeline(t_node_ast *node, t_exec *data)
{
	if (node->left_child->type == T_PIPE)
		exec_pipeline(node->left_child, data);
	if (node->left_child->type == T_CMD)
		exec_pipe(node->left_child, data);
	if (node->right_child->type == T_CMD)
		exec_pipe(node->right_child, data);
}

int exec_master_pipe(t_node_ast *node, t_exec *data)
{
	if (node->left_child->type == T_PIPE)
		exec_pipeline(node->left_child, data);
	else if (node->left_child->type == T_CMD)
	{
		
	}
}