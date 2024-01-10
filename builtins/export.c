/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:07 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 02:22:32 by ybelatar         ###   ########.fr       */
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

void print_justincase(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
        {
            ft_dprintf(2,"bash: export: `%s': not a valid identifier\n" , str);
            return ;
        }
        else if (!ft_isalnum(str[i]) && str[i] != '_')
        {
            ft_dprintf(2,"bash: export: `%s': not a valid identifier\n" , str);
            return ;
        }
        i++;
    }
}

int export_one(char *arg, t_minishell *minishell)
{
    int i;
    char *linus;
    char *boom;

    if (ft_strchri(arg, '=') <= 0)
        return (print_justincase(arg), 0);
    i = 0;
    while (i < ft_strchri(arg, '='))
    {
        if (i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
            return (ft_dprintf(2,"bash: export: `%s': not a valid identifier\n" , arg), 1);
        else if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (ft_dprintf(2,"bash: export: `%s': not a valid identifier\n" , arg), 1);
        i++;
    }
    if (!arg[ft_strchri(arg, '=') + 1])
        return (0);
    linus = ft_substr(arg, 0, ft_strchri(arg, '='));
    boom = ft_substr(arg, ft_strchri(arg, '=') + 1, ft_strlen(arg));
    update_env(linus, boom, minishell->env);
    free(linus);
    free(boom);
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
