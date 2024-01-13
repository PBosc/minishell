/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:29 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/13 16:21:22 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	match_core(char *str, char *pattern, int f[4])
{
	while (str[f[0]])
	{
		if (pattern[f[1]] == '*' || pattern[f[1]] == str[f[0]])
		{
			if (pattern[f[1]] == '*')
			{
				f[2] = f[1]++;
				f[3] = f[0];
			}
			else
				a(&f[1], &f[0]);
		}
		else if (f[2] != -1)
		{
			f[1] = f[2] + 1;
			f[0] = ++f[3];
		}
		else
			return (0);
	}
	while (pattern[f[1]] == '*')
		f[1]++;
	return (pattern[f[1]] == '\0');
}

int	ft_ismatch(char *str, char *pattern)
{
	int	f[4];

	if (!ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
		return (0);
	f[0] = 0;
	f[1] = 0;
	f[2] = -1;
	f[3] = -1;
	return (match_core(str, pattern, f));
}

char	**expanded_wildcard(t_pretoken *pretoken)
{
	char			**tab;
	DIR				*dir;
	struct dirent	*entry;

	if (!ft_strchr(pretoken->content, '*'))
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (clear_pretokens(&pretoken), perror("opendir"), NULL);
	tab = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_ismatch(entry->d_name, pretoken->content))
			tab = join_tab(tab, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (tab);
}

t_pretoken	*new_pretoken_wild(char *str, t_pretoken *pretoken, int *i)
{
	t_pretoken	*new;

	new = new_pretoken(str, WORD);
	new->wild = 1;
	new->next_pretoken = pretoken->next_pretoken;
	*i = *i + 1;
	return (new);
}

void	expand_wildcard(t_pretoken *pretoken)
{
	char		**tab;
	int			i;
	t_pretoken	*new;

	if (ft_strchri(pretoken->content, '*') == -1)
		return ;
	tab = sort_tab(expanded_wildcard(pretoken));
	if (!tab && ft_strchri(pretoken->content, '*') != -1)
		return ;
	i = 0;
	while (tab[i] && tab[i + 1])
	{
		new = new_pretoken_wild(tab[i], pretoken, &i);
		pretoken->next_pretoken = new;
	}
	if (tab[i])
	{
		free(pretoken->content);
		pretoken->content = tab[i];
	}
	free(tab);
}
