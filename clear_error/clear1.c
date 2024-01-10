/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:42:39 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:44:00 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_ast(t_node_ast **ast)
{
	t_node_ast	*tmp_l;
	t_node_ast	*tmp_r;

	if (!ast || !*ast)
		return ;
	tmp_l = (*ast)->left_child;
	tmp_r = (*ast)->right_child;
	if ((*ast)->type == T_CMD)
	{
		clear_tab((*ast)->args);
		clear_redirs(&((*ast)->redirs));
	}
	free(*ast);
	clear_ast(&tmp_l);
	clear_ast(&tmp_r);
}

void	move_def(t_pretoken **pretoken, int i)
{
	t_pretoken	*tmp;

	tmp = (*pretoken)->next_pretoken;
	if (i)
		free((*pretoken)->content);
	free(*pretoken);
	*pretoken = tmp;
}

void	move_def_token(t_token **token, int i)
{
	t_token	*tmp;

	tmp = (*token)->next_token;
	if (i)
		free((*token)->content);
	free(*token);
	*token = tmp;
}
