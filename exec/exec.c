/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:13:06 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/04 15:20:35 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void init_jump_table(int (***exec_fct)(t_node_ast *))
{
	(*exec_fct)[T_CMD] = &exec_cmd;
	(*exec_fct)[T_PIPE] = &exec_pipe;
	(*exec_fct)[T_OR] = &exec_or;
	(*exec_fct)[T_AND] = &exec_and;
}

int		exec(t_node_ast *ast, t_exec *exec)
{
	t_fct_ptr				exec_fct[9];

	init_jump_table(&exec_fct);
	exec_fct[ast->type](ast, exec);
}
