/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:13:48 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/13 16:19:58 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	wild_sort(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (ft_tolower(s1[i]) == ft_tolower(s2[i]))
			return (s2[i] - s1[i]);
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

void	insert(char **tab, int j)
{
	int		k;
	char	*tmp;

	k = j;
	while (k > 0 && wild_sort(tab[k], tab[k - 1]) > 0)
	{
		tmp = tab[k];
		tab[k] = tab[k - 1];
		tab[k - 1] = tmp;
		k--;
	}
}

char	**sort_tab(char **tab)
{
	int	i;

	i = 1;
	while (i < plen(tab))
		insert(tab, i++);
	return (tab);
}
