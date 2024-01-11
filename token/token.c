/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:49:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 03:38:27 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	add_token_word(t_token **tokens, t_pretoken **pretoken)
{
	int		ret;
	char	*content;

	content = NULL;
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

int	add_token(t_token **tokens, t_pretoken **pretoken)
{
	int		ret;
	char	*content;

	content = NULL;
	if ((*pretoken)->type == WORD)
	{
		return (add_token_word(tokens, pretoken));
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
