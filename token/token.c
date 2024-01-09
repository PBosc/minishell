/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:49:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 05:24:50 by ybelatar         ###   ########.fr       */
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

int new_token(t_token **tokens, char *content, t_token_type type)
{
	t_token	*new;
	t_token	*last;

	// if (!content)
	// 	return (0);
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

int match_token(t_token **tokens, t_pretoken *pretoken)
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

/*
	TODO check si execve prend le string avec pls arguments, et dans le cas contraire ne pas join les arg
*/

int	add_token(t_token **tokens, t_pretoken *pretoken)
{
	//t_token	*new;
	//t_token	*last;
	// char	*content;

	//new = NULL;
	//content = NULL;
	// if ((*pretoken)->type == WORD)
	// {
	// 	while ((*pretoken) && (*pretoken)->type == WORD)
	// 	{
	// 		content = ft_strjoin_free(content, (*pretoken)->content);
	// 		move_def(pretoken);
	// 	}
	// 	new = new_token(content, OPERAND);
	// }
	if (pretoken->type == WORD)
		return (new_token(tokens, pretoken->content, OPERAND));
	else if (pretoken->type != WHITESPACE)
		return (match_token(tokens, pretoken));
	else
		return (free(pretoken->content), 1);
	// if (*tokens)
	// {
	// 	last = last_token(*tokens);
	// 	last->next_token = new;
	// }
	// else
	// 	*tokens = new;
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
		if (!add_token(&tokens, pretokens))
			return (printf("Pb de token\n"), clear_tokens(&tokens), NULL);
		//if (pretokens->type == WHITESPACE)
			//move_def(&pretokens, 1);
		move_def(&pretokens, 0);
	}
	return (tokens);
}
