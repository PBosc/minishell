/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_dq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:22 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 00:38:23 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_value_env_dq(char *name, t_minishell *minishell)
{
	char	*res_env;

	if (!ft_strlen(name))
	{
		free(name);
		return (ft_strdup("$"));
	}
	res_env = get_env(name, minishell->env);
	free(name);
	if (!res_env)
		return (ft_strdup(""));
	return (res_env);
}

int	get_len_dq(char *str, int i)
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
		if (!len && !ft_isalpha(str[i + len]) && str[i + len] != '_' && (str[i
					+ len] == '\'' || str[i + len] == '"'))
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

char	*get_name_env_dq(char *str, int *ptr_i, t_minishell *minishell)
{
	char	*name_env;
	int		len;
	int		j;

	*ptr_i = *ptr_i + 1;
	len = get_len_dq(str, *ptr_i);
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
	return (get_value_env_dq(name_env, minishell));
}

char	*expanded_env_dq(char *str, t_minishell *minishell)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			res = ft_strjoin_free2(res, get_name_dq(str, &i));
		else
			res = ft_strjoin_free2(res, get_name_env_dq(str, &i, minishell));
	}
	return (res);
}

void	expand_env_dq(t_pretoken *pretoken, t_minishell *minishell)
{
	char	*tmp;

	if (!ft_strchr(pretoken->content, '$'))
		return ;
	tmp = pretoken->content;
	pretoken->content = expanded_env_dq(pretoken->content, minishell);
	free(tmp);
}
