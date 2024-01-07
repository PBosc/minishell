/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:27 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/06 18:56:42 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	rm_quotes(t_pretoken *pretoken)
{
	char	*content_trim;
	int		len;
	int		i;

	len = ft_strlen(pretoken->content);
	content_trim = malloc(len - 1);
	if (!content_trim)
		return ;
	i = 0;
	while (i < len - 2)
	{
		content_trim[i] = pretoken->content[i + 1];
		i++;
	}
	content_trim[i] = 0;
	free(pretoken->content);
	pretoken->content = content_trim;
}

/*
	TODO changer le retour en int pour remonter l'erreur easy
*/

void	expand_pretokens(t_pretoken *pretokens, t_minishell *minishell)
{
	while (pretokens)
	{
		if (pretokens->type == WORD)
		{
			if (pretokens->content[0] == '\'')
				rm_quotes(pretokens);
			else if (pretokens->content[0] == '"')
			{
				rm_quotes(pretokens);
				expand_env(pretokens, minishell);
			}
			else
			{
				expand_env(pretokens, minishell);
				expand_wildcard(pretokens);
			}
		}
		pretokens = pretokens->next_pretoken;
	}
}
