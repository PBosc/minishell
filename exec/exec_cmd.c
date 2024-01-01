/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:13:00 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/01 15:17:20 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	wait_commands(t_exec *exec)
{
	while (1)
	{
		exec->wpid = wait(&exec->status);
		if (exec->wpid == -1)
			break ;
		if (exec->wpid != exec->pid || exec->ret_value != EXIT_SUCCESS)
			continue ;
		if (WTERMSIG(exec->status) == 2)
			ft_dprintf(STDERR_FILENO, "\n");
		else if (WTERMSIG(exec->status) == 3)
			ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
		if (WIFEXITED(exec->status))
			exec->ret_value = WEXITSTATUS(exec->status);
		else
			exec->ret_value = 128 + WTERMSIG(exec->status);
	}
	return (exec->ret_value);
}

int   exec_cmd(t_node_ast *node, t_exec *exec)
{
	printf("exec_cmd\n");
}
