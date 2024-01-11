/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:03 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 06:23:52 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exit(t_minishell *minishell, t_exec *data)
{
	clear_ast(&minishell->ast);
	clear_env(&(minishell->env));
	close_pipes(data, 1);
	free(minishell);
}

int	exit_minishell(char **tab, t_minishell *minishell, t_exec *data)
{
	int	i;

	printf("exit\n");
	if (!tab || !*tab)
	{
		clear_exit(minishell, data);
		exit(0);
	}
	if (!ft_isatoi(*tab))
	{
		ft_dprintf(2, "minishell: exit : %s: numeric argument required\n",
			*tab);
		clear_exit(minishell, data);
		exit(2);
	}
	i = 0;
	if (tab[i + 1])
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	exit(ft_atoi(*tab));
}
