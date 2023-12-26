/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:56:29 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/26 19:27:47 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int    exec_and(t_node_ast *node, t_exec *exec)
{
	if (node->left_child->token->type == OPERATOR)
		exec(node->left_child);
	else
		return(exec_cmd(node->left_child));
	g_status = wait_commands(exec);
	if (!g_status)
	{
		if (node->right_child->token->type == OPERATOR)
			exec(node->right_child);
		else
			return(exec_cmd(node->right_child));
	}
	else
		return (g_status);
}

int    exec_or(t_node_ast *node, t_exec *exec)
{
	if (node->left_child->token->type == OPERATOR)
		exec(node->left_child);
	else
		return(exec_cmd(node->left_child));
	g_status = wait_commands(exec);
	if (g_status)
	{
		if (node->right_child->token->type == OPERATOR)
			exec(node->right_child);
		else
			return(exec_cmd(node->right_child));
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
