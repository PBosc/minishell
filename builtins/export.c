/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:07 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 00:33:09 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void display_export(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("export %s=\"%s\"\n", env->key, env->value);
		env = env->next_env;
	}
}

int export_one(char *arg, t_minishell *minishell)
{
    int i;

    if (ft_strchri(arg, '=') == -1)
        return (0);
    i = 0;
    while (i < ft_strchri(arg, '='))
    {
        if (i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
            return (ft_dprintf(2,"bash: export: `%s'" , arg), 1);
        else if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (ft_dprintf(2,"bash: export: `%s'" , arg), 1);
        i++;
    }
    if (!arg[ft_strchri(arg, '=') + 1])
        return (0);
    update_env(ft_substr(arg, 0, ft_strchri(arg, '=')), ft_substr(arg, ft_strchri(arg, '='), ft_strlen(arg)), minishell->env);
    return (0);
}

int export(char **args, t_minishell *minishell)
{
    int i;
    int ret;

    if (!*args)
        return (display_export(minishell->env), 0);
    i = 0;
    ret = 0;
    while (args[i])
    {
        if (export_one(args[i], minishell))
            ret = 1;
        i++;
    }
    return (ret);
}
