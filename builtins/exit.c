/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:03 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/08 04:52:28 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void clear_exit(t_minishell *minishell)
{
    clear_ast(&minishell->ast);
    free(minishell);
}

int    exit_minishell(char **tab, t_minishell *minishell)
{
    int i;

    printf("exit\n");
    if (!tab || !*tab)
    {
        clear_exit(minishell);
        exit(0);
    }
    if (!ft_isatoi(*tab))
    {
        clear_exit(minishell);
        ft_dprintf(2, "minishell: exit : %s: numeric argument required\n", *tab);
        exit(2);
    }
    i = 0;
    if (tab[i + 1])
    {
        ft_dprintf(2, "minishell: exit: too many arguments\n");
        return (2);
    }
    exit(ft_atoi(*tab));
}
