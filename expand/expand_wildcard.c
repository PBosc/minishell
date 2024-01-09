/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:29 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 05:00:35 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
/*
	TODO remonter les mallocs errors
*/

int	is_match(char *s, char *p)
{
	int	i;
	int	s_idx;
	int	p_idx;
	int	last_wildcard_idx;
	int	s_backtrack_idx;
	int	next_to_wildcard_idx;

	if (!ft_strcmp(s, ".") || !ft_strcmp(s, ".."))
		return (0);
	s_idx = 0;
	p_idx = 0;
	last_wildcard_idx = -1;
	s_backtrack_idx = -1;
	next_to_wildcard_idx = -1;
	while (s_idx < ft_strlen(s))
	{
		if (p_idx < ft_strlen(p) && (p[p_idx] == '?' || p[p_idx] == s[s_idx]))
		{
			++s_idx;
			++p_idx;
		}
		else if (p_idx < ft_strlen(p) && p[p_idx] == '*')
		{
			last_wildcard_idx = p_idx;
			next_to_wildcard_idx = ++p_idx;
			s_backtrack_idx = s_idx;
		}
		else if (last_wildcard_idx == -1)
			return (0);
		else
		{
			p_idx = next_to_wildcard_idx;
			s_idx = ++s_backtrack_idx;
		}
	}
	i = p_idx;
	while (i < ft_strlen(p))
	{
		if (p[i] != '*')
			return (0);
		i++;
	}
	return (1);
}


char	**expanded_wildcard(t_pretoken *pretoken)
{
	char **tab;
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
		if (is_match(entry->d_name, pretoken->content))
			tab = join_tab(tab, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (tab);
}



void	expand_wildcard(t_pretoken *pretoken)
{
	char **tab;
	int i;
	t_pretoken *new;

	tab = expanded_wildcard(pretoken);
	if (!tab && ft_strchri(pretoken->content, '*') != -1)
	{
		free(pretoken->content);
		pretoken->content = ft_strdup("");
		return ;
	}
	if (!tab && ft_strchri(pretoken->content, '*') == -1)
		return ;
	i = 0;
	while (tab[i] && tab[i + 1])
	{
		new = new_pretoken(tab[i], WORD);
		new->next_pretoken = pretoken->next_pretoken;
		pretoken->next_pretoken = new;
		i++;
	}
	if (tab[i])
	{
		free(pretoken->content);
		pretoken->content = tab[i];
	}
}

