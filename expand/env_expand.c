/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:22 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 00:37:10 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(char *name, t_pretoken *pretoken, t_minishell *minishell,
		int c)
{
	char	*res_env;

	if (!ft_strlen(name))
	{
		free(name);
		if (!c && is_emptyquote_next(pretoken))
			return (ft_strdup(""));
		else
			return (ft_strdup("$"));
	}
	res_env = get_env(name, minishell->env);
	free(name);
	if (!res_env)
		return (ft_strdup(""));
	return (res_env);
}

int	get_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len])
	{
		if (!len && str[i + len] == '?')
		{
			len++;
			break ;
		}
		if (!ft_isalnum(str[i + len]) && str[i + len] != '_')
			break ;
		if (!len && !ft_isalpha(str[i + len]) && str[i + len] != '_')
		{
			len++;
			break ;
		}
		else if (!ft_isalnum(str[i + len]) && str[i + len] != '_')
			break ;
		len++;
	}
	return (len);
}

char	*get_name_env(char *str, int *ptr_i, t_pretoken *pretoken,
		t_minishell *minishell)
{
	char	*name_env;
	int		len;
	int		j;

	*ptr_i = *ptr_i + 1;
	len = get_len(str, *ptr_i);
	name_env = malloc(len + 1);
	if (!name_env)
		return (NULL);
	j = 0;
	while (j < len)
	{
		name_env[j++] = str[*ptr_i];
		*ptr_i = *ptr_i + 1;
	}
	name_env[j] = 0;
	return (get_value_env(name_env, pretoken, minishell, str[*ptr_i]));
}

char	*expanded_env(char *str, t_pretoken *pretoken, t_minishell *minishell)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			res = ft_strjoin_free2(res, get_name(str, &i));
		else
			res = ft_strjoin_free2(res, get_name_env(str, &i, pretoken,
						minishell));
	}
	return (res);
}

void	expand_env(t_pretoken *pretoken, t_minishell *minishell)
{
	char	*tmp;
	char	*res;

	if (!ft_strchr(pretoken->content, '$'))
		return ;
	tmp = pretoken->content;
	res = expanded_env(pretoken->content, pretoken, minishell);
	if (*res == '\'' || *res == '"')
		res = rm_quotes(res);
	if (!has_whitespace(res))
		pretoken->content = res;
	else
	{
		split_expand(res, pretoken);
		free(res);
	}
	free(tmp);
}
