/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:28:07 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 05:20:04 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	plen(char **map)
{
	int	i;

	if (!map || !(*map))
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**join_tab(char **tab, char *str)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (plen(tab) + 2));
	if (!res)
		return (NULL);
	if (!tab || !(*tab))
	{
		res[0] = str;
		res[1] = NULL;
		return (res);
	}
	i = 0;
	while (tab[i])
	{
		res[i] = tab[i];
		i++;
	}
	res[i++] = str;
	res[i] = NULL;
	free(tab);
	return (res);
}

t_node_type	get_type(t_token_type type)
{
	if (type == AND)
		return (T_AND);
	if (type == OR)
		return (T_OR);
	if (type == PIPEPIPE)
		return (T_PIPE);
	return (T_PIPE);
}
