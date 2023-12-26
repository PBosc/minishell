/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operations_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:57:14 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/26 19:25:21 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int    exec_redirect_out(t_node_ast *node, t_exec *exec)
{
	printf("exec_redirect_out\n");
}

int    exec_redirect_append(t_node_ast *node, t_exec *exec)
{
	printf("exec_redirect_append\n");
}

int	exec_heredoc(t_node_ast *node, t_exec *exec)
{
	printf("exec_heredoc\n");
}

int	exec_nothing(t_node_ast *node, t_exec *exec)
{
	printf("exec_nothing\n");
}