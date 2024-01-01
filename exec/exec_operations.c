/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:56:29 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/01 15:17:42 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int    exec_and(t_node_ast *node, t_exec *data)
{
	if (node->left_child->token->type == OPERATOR)
		exec(node->left_child, data);
	else
		return(exec_cmd(node->left_child, data));
	g_status = wait_commands(data);
	if (!g_status)
	{
		if (node->right_child->token->type == OPERATOR)
			exec(node->right_child, data);
		else
			return(exec_cmd(node->right_child, data));
	}
	else
		return (g_status);
}

int    exec_or(t_node_ast *node, t_exec *data)
{
	if (node->left_child->token->type == OPERATOR)
		exec(node->left_child, data);
	else
		return(exec_cmd(node->left_child, data));
	g_status = wait_commands(data);
	if (g_status)
	{
		if (node->right_child->token->type == OPERATOR)
			exec(node->right_child, data);
		else
			return(exec_cmd(node->right_child, data));
	}
	else
		return (g_status);
}

int    exec_pipe(t_node_ast *node, t_exec *exec)
{
	printf("exec_pipe\n");
}

int    exec_semicolon(t_node_ast *node, t_exec *exec)
{
	printf("exec_cmd\n");
}

int    exec_redirect_in(t_node_ast *node, t_exec *exec)
{
	printf("exec_redirect_in\n");
}
