/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:41:31 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 00:55:44 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_tab_2d(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	starts_with(char *str, char *start)
{
	int	i;

	i = 0;
	while (str[i] == start[i] && start[i])
		i++;
	if (start[i])
		return (0);
	return (1);
}

char	*ft_trim(char *str, int start)
{
	char	*tmp;

	tmp = ft_strdup(str + start);
	free(str);
	return (tmp);
}

char	*get_valid_path(char **paths, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	if (!paths || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.'))
		|| cmd[0] == '/')
		return (free_tab_2d(paths), cmd);
	else if (!paths || !cmd[0])
		return (free_tab_2d(paths), ft_dprintf(2, "minishell: %s: \
command not found\n", cmd), free(cmd), NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (free(cmd), free_tab_2d(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (free_tab_2d(paths), cmd);
	ft_dprintf(2, "minishell: %s: command not found\n", cmd);
	free(cmd);
	return (free_tab_2d(paths), ft_strdup("placeholder1234"));
}

char	**get_path(t_env *env)
{
	char	**path;

	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
		{
			path = ft_split(env->value, ':');
			return (path);
		}
		env = env->next_env;
	}
	return (NULL);
}
