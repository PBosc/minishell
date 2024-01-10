/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:45:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 00:25:13 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(char **args, t_minishell *minishell)
{
    if (!*args)
    {
        return (ft_dprintf(2, "bash: cd: too few arguments\n"), 1);
        // if (chdir(get_env("HOME", minishell->env)) == -1)
        //     return (ft_dprintf(2, "bash : cd: %s\n", strerror(errno)), 1);
        // update_env("OLD_PWD", get_env("PWD", minishell->env), minishell->env, 0);
        // update_env("PWD", get_env("HOME", minishell->env), minishell->env, 0);
        // return (0);
    }
    if (*(args + 1))
        return (ft_dprintf(2, "bash: cd: too many arguments\n"), 1);
    if (chdir(*args) == -1)
        return (ft_dprintf(2, "bash : cd: %s\n", strerror(errno)), 1);
    update_env("OLDPWD", get_env("PWD", minishell->env), minishell->env);
    update_env("PWD", *args, minishell->env);
    return (0);
}
