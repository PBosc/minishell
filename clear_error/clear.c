/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:19:55 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:43:08 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_pretokens(t_pretoken **pretokens)
{
	t_pretoken	*tmp;

	if (!pretokens || !*pretokens)
		return ;
	while (*pretokens)
	{
		tmp = (*pretokens)->next_pretoken;
		free((*pretokens)->content);
		free(*pretokens);
		*pretokens = tmp;
	}
}

void	clear_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next_token;
		free(*tokens);
		*tokens = tmp;
	}
}

void	clear_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clear_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next_env;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

void	clear_redirs(t_redir_list **redirs)
{
	t_redir_list	*tmp;

	if (!redirs || !*redirs)
		return ;
	while (*redirs)
	{
		tmp = (*redirs)->next_redir;
		free((*redirs)->file);
		free(*redirs);
		*redirs = tmp;
	}
}
