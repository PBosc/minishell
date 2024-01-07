/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:45:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/06 23:06:48 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int cd(char **args, t_minishell *minishell)
{
    if (!*args)
        return (ft_dprintf(2, "bash: cd: too many arguments\n"), 1);
    if (chdir(*args) == -1)
        return (ft_dprintf(2, "bash : cd: %s\n", /*probleme*/""), 1);
    update_env("OLD_PWD", get_env("PWD", minishell->env), minishell->env);
    update_env("PWD", *args, minishell->env);
    return (0);
}