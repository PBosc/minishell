/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:59:08 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/11 23:45:55 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_data(t_exec *data, t_env *env)
{
	data->env = env;
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->prev_pipe = -1;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->is_pipe = 0;
	data->ret_value = EXIT_SUCCESS;
	data->is_here_doc = 0;
}

char	*get_one(t_env *env)
{
	char	*res;

	res = ft_strjoin(env->key, "=");
	res = ft_strjoin_free(res, env->value);
	return (res);
}

char	**tab_env(t_env *env)
{
	char	**res;

	if (!env)
		return (NULL);
	res = NULL;
	while (env)
	{
		res = join_tab(res, get_one(env));
		env = env->next_env;
	}
	return (res);
}
