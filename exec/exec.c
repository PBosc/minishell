/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:13:06 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/26 19:25:33 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void init_jump_table(int (***exec_fct)(t_node_ast *))
{
	(*exec_fct)[0] = &exec_and;
	(*exec_fct)[1] = &exec_or;
	(*exec_fct)[2] = &exec_pipe;
	(*exec_fct)[3] = &exec_semicolon;
	(*exec_fct)[4] = &exec_redirect_in;
	(*exec_fct)[5] = &exec_redirect_out;
	(*exec_fct)[6] = &exec_redirect_append;
	(*exec_fct)[7] = &exec_heredoc;
	(*exec_fct)[8] = &exec_nothing;
}

int		exec(t_node_ast *ast)
{
	static e_operator_type	ope_type = NOTHING;
	(int)(*exec_fct[9])(t_node_ast *, t_exec *);

	init_jump_table(&exec_fct);
	if (ast->token->type == OPERATOR)
		return (exec_fct[ast->token->ope_type](ast));
	else
		return(0);
}
