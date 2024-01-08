/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:13:06 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/08 01:25:11 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int g_status;

void init_jump_table(t_fct_ptr (*exec_fct)[4])
{
	(*exec_fct)[T_CMD] = &exec_cmd;
	(*exec_fct)[T_PIPE] = &exec_master_pipe;
	(*exec_fct)[T_OR] = &exec_or;
	(*exec_fct)[T_AND] = &exec_and;
}

int		exec(t_node_ast *ast, t_exec *exec)
{
	t_fct_ptr				exec_fct[4];

	init_jump_table(&exec_fct);
	exec_fct[ast->type](ast, exec);
	g_status = wait_commands(exec);
	return (0);
}

