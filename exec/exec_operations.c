/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:56:29 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/08 20:21:50 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_and(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (node->left_child->type != T_CMD)
		exec(node->left_child, data, minishell);
	else
		exec_cmd(node->left_child, data, minishell);
	g_status = wait_commands(data);
	if (g_status)
	{
		if (node->right_child->type != T_CMD)
			return (exec(node->right_child, data, minishell));
		else
			return (exec_cmd(node->right_child, data, minishell));
	}
	else
		return (g_status);
}

int	exec_or(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (node->left_child->type != T_CMD)
		exec(node->left_child, data, minishell);
	else
		exec_cmd(node->left_child, data, minishell);
	g_status = wait_commands(data);
	if (!g_status)
	{
		if (node->right_child->type != T_CMD)
			return (exec(node->right_child, data, minishell));
		else
			return (exec_cmd(node->right_child, data, minishell));
	}
	else
		return (g_status);
}
