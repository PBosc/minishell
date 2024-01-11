/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:51:23 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 03:10:22 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env_doc(char *name, t_minishell *minishell)
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

char	*get_name_env_doc(char *str, int *ptr_i, t_minishell *minishell)
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
	return (get_value_env_doc(name_env, minishell));
}

char	*expanded_heredoc(char *str, t_minishell *minishell)
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
			res = ft_strjoin_free2(res, get_name_env_doc(str, &i, minishell));
	}
	free(str);
	return (res);
}
