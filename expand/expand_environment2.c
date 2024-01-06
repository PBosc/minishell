/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:22 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/05 19:44:37 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
TODO case when env variable is a string with spaces
	-> need to seperate the different words in tokens
*/
	// tmp = pretoken->next_pretoken;
	// while (ft_strchr(pretoken->content, '$'))
/*
	TODO remonter les mallocs errors
*/


// char	**expanded_env(t_pretoken *pretoken)
// {
// 	int		i;
// 	char	*name;
// 	char	*env_value;

// 	i = 0;
// 	name = get_name(pretoken->content, &i);
// 	if (!name)
// 		return (pretoken->content);
// 	if (!ft_strlen(name))
// 	{
// 		if (is_empty_next(pretoken))
// 			return (ft_strdup(""));
// 		else
// 			return (ft_strdup("$"));
// 	}
// 	env_value = getenv(name);
// 	if (!env_value && !pretoken->content[i])
// 		return (NULL);
// 	if (!env_value)
// 		return (ft_strjoin(ft_substr(pretoken->content, 0, ft_strchri(pretoken->content, '$')),
// 				expanded_env(pretoken->content + i, pretoken)));
// 	return (ft_strjoin(ft_strjoin(ft_substr(pretoken->content, 0, ft_strchri(pretoken->content, '$')),
// 				env_value), expanded_env(pretoken->content + i, pretoken)));
// }

char	*get_name(char *str, int *ptr_i)
{
	int		j;
	int		len;
	char	*res;

	len = 0;
	if (str[*ptr_i] == '$')
	{
		len++;
		while (str[*ptr_i + len] && ft_isalnum(str[*ptr_i + len]))
			len++;
	}
	else
	{
		while (str[*ptr_i + len] && )
			len++;
	}
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len)
	{
		res[j++] = str[*ptr_i];
		*ptr_i = *ptr_i + 1;
	}
	res[j] = 0;
	while (str[*ptr_i] && !ft_isalnum(str[*ptr_i]) && str[*ptr_i] != '$')
		*ptr_i = *ptr_i + 1;
	return (res);
}

int	is_empty_next(t_pretoken *pretoken)
{
	if (pretoken->next_pretoken == NULL
		|| pretoken->next_pretoken->type == WHITESPACE
		|| !ft_strcmp(pretoken->next_pretoken->content, "''")
		|| !ft_strcmp(pretoken->next_pretoken->content, "\"\""))
		return (1);
	return (0);
}

char	**expanded_env(t_pretoken *pretoken)
{
	int		i;
	char	*name;
	char	*env_value;
	char **tab;

	if (!ft_strchr(pretoken->content, '$'))
		return (NULL);
	i = 0;
	tab = NULL;
	while (pretoken->content[i])
	{
		name = get_name(pretoken->content, &i);
		if (!name)
			return (NULL);
		// if (!*name)
		// {
		// 	if (is_empty_next(pretoken))
		// 		return (ft_strdup(""));
		// 	else
		// 		return (ft_strdup("$"));
		// }
		if (*name == '$')
		{
			env_value = getenv(name + 1);
			if (env_value)
				tab = join_tab(tab, env_value);
		}
		else
			tab = join_tab(tab, name);
		//free(name);
		//i++;
	}
	return (tab);
}

void	expand_env(t_pretoken *pretoken)
{
	t_pretoken *new;
	char **tab;
	int i;

	tab = expanded_env(pretoken);
	if (!tab)
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

