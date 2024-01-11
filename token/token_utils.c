/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:42:49 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 00:43:28 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next_token)
		token = token->next_token;
	return (token);
}

int	new_token(t_token **tokens, char *content, t_token_type type)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = content;
	new->type = type;
	new->next_token = NULL;
	if (*tokens)
	{
		last = last_token(*tokens);
		last->next_token = new;
	}
	else
		*tokens = new;
	return (1);
}
