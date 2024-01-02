/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:29 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 02:57:55 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		isMatch(char *s, char *p);
char	*expanded_wildcard(char *str);

void	expand_wildcard(t_pretoken *pretoken)
{
	pretoken->content = expanded_wildcard(pretoken->content);
}

int	is_match(char *s, char *p)
{
	int	i;
	int	s_idx;
	int	p_idx;
	int	last_wildcard_idx;
	int	s_backtrack_idx;
	int	next_to_wildcard_idx;

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

/*
	TODO '.' et '..' a retirer des wildcards
*/
char	*expanded_wildcard(char *str)
{
	char			*expanded;
	DIR				*dir;
	struct dirent	*entry;

	if (!ft_strchr(str, '*'))
		return (str);
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	entry = readdir(dir);
	expanded = ft_strdup("");
	while (entry)
	{
		if (is_match(entry->d_name, str))
		{
			expanded = ft_strjoin_free(expanded, entry->d_name);
			expanded = ft_strjoin_free(expanded, " ");
		}
		entry = readdir(dir);
	}
	closedir(dir);
	free(str);
	return (expanded);
}
