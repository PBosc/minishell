/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:49:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 03:00:23 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next_token)
		token = token->next_token;
	return (token);
}

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next_token = NULL;
	return (new);
}

t_token	*match_token(t_pretoken *pretoken)
{
	if (pretoken->type == OPEN_PAR)
		return (new_token(pretoken->content, OPEN_P));
	if (pretoken->type == CLOSED_PAR)
		return (new_token(pretoken->content, CLOSED_P));
	if (pretoken->type == PIPE)
		return (new_token(pretoken->content, PIPEPIPE));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, "<"))
		return (new_token(pretoken->content, REDIRECT_IN));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, ">"))
		return (new_token(pretoken->content, REDIRECT_OUT));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, "<<"))
		return (new_token(pretoken->content, HEREDOC));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, ">>"))
		return (new_token(pretoken->content, REDIRECT_APPEND));
	if (pretoken->type == OPERATOR && !ft_strcmp(pretoken->content, "||"))
		return (new_token(pretoken->content, OR));
	if (pretoken->type == OPERATOR && !ft_strcmp(pretoken->content, "&&"))
		return (new_token(pretoken->content, AND));
	return (NULL);
}

void	add_token(t_token **tokens, t_pretoken **pretoken)
{
	t_token	*new;
	t_token	*last;
	char	*content;

	new = NULL;
	content = NULL;
	if ((*pretoken)->type == WORD)
	{
		while ((*pretoken) && (*pretoken)->type == WORD)
		{
			content = ft_strjoin_free(content, (*pretoken)->content);
			(*pretoken) = (*pretoken)->next_pretoken;
		}
		new = new_token(content, OPERAND);
	}
	else if ((*pretoken)->type != WHITESPACE)
	{
		new = match_token(*pretoken);
		(*pretoken) = (*pretoken)->next_pretoken;
	}
	else
	{
		(*pretoken) = (*pretoken)->next_pretoken;
		return ;
	}
	if (*tokens)
	{
		last = last_token(*tokens);
		last->next_token = new;
	}
	else
		*tokens = new;
}

t_token	*tokenization(t_pretoken *pretokens)
{
	t_token	*tokens;

	tokens = NULL;
	while (pretokens)
		add_token(&tokens, &pretokens);
	return (tokens);
}
