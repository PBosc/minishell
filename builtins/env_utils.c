/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:23 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/08 05:00:06 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "parsing.h"

void display_env(t_env *env)
{
	if (!env)
    {
        printf("rien\n");
		return ;
    }
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next_env;
	}
}

char *get_env(char *key, t_env *env)
{
    if (!env)
        return (NULL);
    while (env)
    {
        if (!ft_strcmp(env->key, key))
            return (env->value);
        env = env->next_env;
    }
    return (NULL);
}

void    update_env(char *key, char *value, t_env *env)
{
    if (!env)
        env = new_env(key, value, 0);
    while (env->next_env)
    {
        if (!ft_strcmp(env->key, key))
        {
            /*
            ! pe il faut free le result de getenv ici
            */
            env->value = value;
        }
        env = env->next_env;
    }
    if (!ft_strcmp(env->key, key))
    {
        
        env->value = value;
    }
    else
        env->next_env = new_env(key, value, 0);
}

void    delete_env(char *key, t_env *env, t_minishell *minishell)
{
    t_env *prev;
    
    if (!env)
        return ;
    prev = NULL;
    while (env)
    {
        if (!ft_strcmp(env->key, key))
        {
            if (!prev)
                minishell->env = env->next_env;
            else
                prev->next_env = env->next_env;
            free(env->key);
            free(env->value);
            free(env);
        }
        prev = env;
        env = env->next_env;
    }
}