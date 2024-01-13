/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:59:08 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 21:29:19 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->pid = 0;
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

int	id(char *path)
{
	struct stat	*path_stat;
	int			ret;

	path_stat = ft_calloc(1, sizeof(struct stat));
	stat(path, path_stat);
	ret = !S_ISREG(path_stat->st_mode);
	free(path_stat);
	return (ret);
}

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}
