/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:22 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 06:39:02 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
TODO case when env variable is a string with spaces
	-> need to seperate the different words in tokens
    suffit juste de split quand c pas expand de double quotes et faire
    la meme que expand wildcard
    + rajouter le $?
    + recoder le getenv pcque ya moyen que l'env se refresh pas pendant lexec c sur meme
*/
char *get_name_utils(char *str, int i, int *ptr_i)
{
	int len;
	char *res;
	int j;

	len = 0;
	while (str[i + len] && ft_isalnum(str[i + len]))
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len)
		res[j++] = str[i++];
	res[j] = 0;
	*ptr_i = i;
	return (res);
}

char	*get_name(char *str, int *ptr_i)
{
	int		i;
	//int		j;
	//int		len;
	//char	*res;

	i = 0;
	//len = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i++])
		return (NULL);
	if (str[i] == '?')
	{
		*ptr_i = i + 1;	
		return (ft_strdup("?"));
	}
	// while (str[i + len] && ft_isalnum(str[i + len]))
	// 	len++;
	// res = malloc(len + 1);
	// if (!res)
	// 	return (NULL);
	// j = 0;
	// while (j < len)
	// 	res[j++] = str[i++];
	// res[j] = 0;
	// *ptr_i = i;
	return (get_name_utils(str, i, ptr_i));
}

int	is_empty_next(t_pretoken *pretoken)
{
	if (pretoken->next_pretoken == NULL
		|| pretoken->next_pretoken->type == WHITESPACE)
		return (1);
	return (0);
}

char	*expanded_env(char *str, t_pretoken *pretoken, t_minishell *minishell)
{
	int		i;
	char	*name;
	char	*env_value;

	i = 0;
	name = get_name(str, &i);
	if (!name)
		return (str);
	if (!ft_strlen(name))
	{
		if (!is_empty_next(pretoken))
			return (free(name), ft_strdup(""));
		else
			return (free(name), ft_strdup("$"));
	}
	env_value = get_env(name, minishell->env);
	free(name);
	if (!env_value && !str[i])
		return (ft_strdup(""));
	if (!env_value)
		return (ft_strjoin(ft_substr(str, 0, ft_strchri(str, '$')),
				expanded_env(str + i, pretoken, minishell)));
	return (ft_strjoin(ft_strjoin(ft_substr(str, 0, ft_strchri(str, '$')),
				env_value), expanded_env(str + i, pretoken, minishell)));
}




void	expand_env(t_pretoken *pretoken, t_minishell *minishell)
{
	char *tmp;
	
	if (!ft_strchr(pretoken->content, '$'))
		return ;
	tmp = pretoken->content;
	pretoken->content = expanded_env(pretoken->content, pretoken, minishell);
	free(tmp);
}

