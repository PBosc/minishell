/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 02:24:22 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 02:52:52 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	q3(t_pretoken *pretokens, int i)
{
	if (!pretokens)
		return (0);
	if (pretokens->type == REDIR)
		return ((q2(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == WORD)
		return ((q1(skip_spaces(pretokens->next_pretoken), i)));
	else
		return (0);
}

int	q4(t_pretoken *pretokens, int i)
{
	if (!pretokens)
		return (0);
	if (pretokens->type == WORD)
		return ((q1(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == REDIR)
		return ((q2(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == OPEN_PAR)
		return ((q4(skip_spaces(pretokens->next_pretoken), i + 1)));
	else
		return (0);
}

int	q5(t_pretoken *pretokens, int i)
{
	if (!pretokens && i == 0)
		return (1);
	if (!pretokens && i != 0)
		return (0);
	if (pretokens->type == OPERATOR)
		return ((q4(skip_spaces(pretokens->next_pretoken), i)));
	else if (pretokens->type == CLOSED_PAR)
		return ((q5(skip_spaces(pretokens->next_pretoken), i - 1)));
	else if (pretokens->type == PIPE)
		return ((q3(skip_spaces(pretokens->next_pretoken), i)));
	else
		return (0);
}
