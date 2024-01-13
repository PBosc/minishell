/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:13:06 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 22:43:25 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	g_status;

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_minishell *minishell, t_exec *data)
{
	if (ft_strcmp(args[0], "echo") == 0)
		g_status = echo(args + 1);
	else if (ft_strcmp(args[0], "cd") == 0)
		g_status = cd(args + 1, minishell);
	else if (ft_strcmp(args[0], "pwd") == 0)
		g_status = pwd(args + 1, minishell);
	else if (ft_strcmp(args[0], "export") == 0)
		g_status = export(args + 1, minishell);
	else if (ft_strcmp(args[0], "unset") == 0)
		g_status = unset(args + 1, minishell);
	else if (ft_strcmp(args[0], "env") == 0)
		g_status = env(minishell);
	else if (ft_strcmp(args[0], "exit") == 0)
		g_status = exit_minishell(args + 1, minishell);
	if (data->is_pipe)
	{
		clear_ast(&minishell->ast);
		clear_env(&minishell->env);
		free(minishell);
	}
	return (g_status);
}

void	init_jump_table(t_fct_ptr (*exec_fct)[4])
{
	(*exec_fct)[T_CMD] = &exec_cmd;
	(*exec_fct)[T_PIPE] = &exec_master_pipe;
	(*exec_fct)[T_OR] = &exec_and;
	(*exec_fct)[T_AND] = &exec_or;
}

int	exec(t_node_ast *ast, t_exec *exec, t_minishell *minishell)
{
	t_fct_ptr	exec_fct[4];

	init_jump_table(&exec_fct);
	exec_fct[ast->type](ast, exec, minishell);
	wait_commands(exec);
	return (0);
}
