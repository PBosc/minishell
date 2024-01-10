/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:49:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:48:54 by ybelatar         ###   ########.fr       */
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

int	match_token(t_token **tokens, t_pretoken *pretoken)
{
	if (pretoken->type == OPEN_PAR)
		return (new_token(tokens, pretoken->content, OPEN_P));
	if (pretoken->type == CLOSED_PAR)
		return (new_token(tokens, pretoken->content, CLOSED_P));
	if (pretoken->type == PIPE)
		return (new_token(tokens, pretoken->content, PIPEPIPE));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, "<"))
		return (new_token(tokens, pretoken->content, REDIRECT_IN));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, ">"))
		return (new_token(tokens, pretoken->content, REDIRECT_OUT));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, "<<"))
		return (new_token(tokens, pretoken->content, HEREDOC));
	if (pretoken->type == REDIR && !ft_strcmp(pretoken->content, ">>"))
		return (new_token(tokens, pretoken->content, REDIRECT_APPEND));
	if (pretoken->type == OPERATOR && !ft_strcmp(pretoken->content, "||"))
		return (new_token(tokens, pretoken->content, OR));
	if (pretoken->type == OPERATOR && !ft_strcmp(pretoken->content, "&&"))
		return (new_token(tokens, pretoken->content, AND));
	return (0);
}

int	add_token(t_token **tokens, t_pretoken **pretoken)
{
	int		ret;
	char	*content;

	content = NULL;
	if ((*pretoken)->type == WORD)
	{
		if ((*pretoken)->wild == 1)
		{
			ret = new_token(tokens, (*pretoken)->content, OPERAND);
			move_def(pretoken, 0);
			return (ret);
		}
		while ((*pretoken) && (*pretoken)->type == WORD && !(*pretoken)->wild)
		{
			content = ft_strjoin_free2(content, (*pretoken)->content);
			move_def(pretoken, 0);
		}
		return (new_token(tokens, content, OPERAND));
	}
	else if ((*pretoken)->type != WHITESPACE)
	{
		ret = match_token(tokens, *pretoken);
		move_def(pretoken, 0);
		return (ret);
	}
	else
	{
		free((*pretoken)->content);
		move_def(pretoken, 0);
		return (1);
	}
	return (0);
}

t_token	*tokenization(t_pretoken *pretokens)
{
	t_token	*tokens;

	if (!check_syntax(pretokens))
		return (clear_pretokens(&pretokens), NULL);
	tokens = NULL;
	while (pretokens)
	{
		if (!add_token(&tokens, &pretokens))
			return (clear_pretokens(&pretokens), clear_tokens(&tokens), NULL);
	}
	return (tokens);
}
