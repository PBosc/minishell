/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:50:14 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 05:51:39 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_pretoken	*skip_spaces(t_pretoken *pretokens)
{
	if (!pretokens)
		return (NULL);
	while (pretokens && pretokens->type == WHITESPACE)
	{
		pretokens = pretokens->next_pretoken;
	}
	return (pretokens);
}

int	check_syntax(t_pretoken *pretokens)
{
	return (q0(skip_spaces(pretokens), 0));
}

int	q0(t_pretoken *pretokens, int i)
{
	if (!pretokens && i == 0)
		return (1);
	if (!pretokens && i != 0)
		return (syntax_error(pretokens), 0);
	if (pretokens->type == WORD)
		return (q1(skip_spaces(pretokens->next_pretoken), i));
	else if (pretokens->type == REDIR)
		return (q2(skip_spaces(pretokens->next_pretoken), i));
	else if (pretokens->type == OPEN_PAR)
		return (q0(skip_spaces(pretokens->next_pretoken), i + 1));
	else
		return (syntax_error(pretokens), 0);
}

int	q1(t_pretoken *pretokens, int i)
{
	if (!pretokens && i == 0)
		return (1);
	if (!pretokens && i != 0)
		return (syntax_error(pretokens), 0);
	if (pretokens->type == WORD)
		return ((q1(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == REDIR)
		return ((q2(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == CLOSED_PAR)
		return ((q5(skip_spaces(pretokens->next_pretoken), i - 1)));
	else if (pretokens->type == PIPE)
		return ((q3(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == OPERATOR)
		return ((q4(skip_spaces(pretokens->next_pretoken), i)));
	else
		return (syntax_error(pretokens), 0);
}

int	q2(t_pretoken *pretokens, int i)
{
	if (!pretokens)
		return (syntax_error(pretokens), 0);
	if (pretokens->type == WORD)
		return ((q1(skip_spaces(pretokens->next_pretoken), i)));
	else
		return (syntax_error(pretokens), 0);
}
