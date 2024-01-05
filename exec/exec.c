/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:13:06 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/05 00:56:48 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int g_status;

void init_jump_table(t_fct_ptr (*exec_fct)[9])
{
	(*exec_fct)[T_CMD] = &exec_cmd;
	(*exec_fct)[T_PIPE] = &exec_pipeline;
	(*exec_fct)[T_OR] = &exec_or;
	(*exec_fct)[T_AND] = &exec_and;
}

int		exec(t_node_ast *ast, t_exec *exec)
{
	t_fct_ptr				exec_fct[9];

	init_jump_table(&exec_fct);
	exec_fct[ast->type](ast, exec);
	return (0);
}

int main(int argc, char const *argv[], char **env)
{
	t_exec		data;
	t_node_ast	*ast;

	ast = create_node(T_PIPE);
	data.env = env;
	data.fd_in = STDIN_FILENO;
	data.fd_out = STDOUT_FILENO;
	data.prev_pipe = -1;
	data.pipe[0] = -1;
	data.pipe[1] = -1;
	ast->left_child = create_node(T_CMD);
	ast->left_child->args = malloc(sizeof(char *) * 2);
	ast->left_child->args[0] = ft_strdup("ls");
	ast->left_child->args[2] = NULL;
	ast->right_child = create_node(T_CMD);
	ast->right_child->args = malloc(sizeof(char *) * 3);
	ast->right_child->args[0] = ft_strdup("cat");
	ast->right_child->args[1] = ft_strdup("-e");
	ast->right_child->args[2] = NULL;
	exec(ast, &data);
	g_status = wait_commands(&data);
	return g_status;
}
