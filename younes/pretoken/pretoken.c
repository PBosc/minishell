/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:50:04 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 03:07:39 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
				i++;
			if (!str[i])
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}

t_pretoken	*last_pretoken(t_pretoken *pretoken)
{
	if (!pretoken)
		return (NULL);
	while (pretoken->next_pretoken)
		pretoken = pretoken->next_pretoken;
	return (pretoken);
}

void	add_pretoken(t_pretoken **pretoken, char *content, t_pretoken_type TYPE)
{
	t_pretoken	*new;
	t_pretoken	*last;

	last = last_pretoken(*pretoken);
	new = malloc(sizeof(t_pretoken));
	if (!new)
		return ;
	new->content = content;
	new->type = TYPE;
	new->next_pretoken = NULL;
	if (!(*pretoken))
		*pretoken = new;
	else
		last->next_pretoken = new;
}

t_pretoken	*pretokenization(char *str)
{
	t_pretoken	*pretokens;
	int			i;

	i = 0;
	if (!str || !check_quotes(str))
		return (NULL);
	pretokens = NULL;
	while (str[i])
	{
		if (str[i] == '(')
			add_pretoken(&pretokens, char_to_string(str[i++]), OPEN_PAR);
		else if (str[i] == ')')
			add_pretoken(&pretokens, char_to_string(str[i++]), CLOSED_PAR);
		else if (is_whitespace(str[i]))
			add_pretoken(&pretokens, get_whitespace(str, &i), WHITESPACE);
		else if (str[i] == '|' && str[i + 1] != '|')
			add_pretoken(&pretokens, char_to_string(str[i++]), PIPE);
		else if (str[i] == '|' && str[i + 1] == '|')
			add_pretoken(&pretokens, get_operator(str, &i), OPERATOR);
		else if (str[i] == '&' && str[i + 1] == '&')
			add_pretoken(&pretokens, get_operator(str, &i), OPERATOR);
		else if (str[i] == '>' || str[i] == '<')
			add_pretoken(&pretokens, get_redir(str, &i), REDIR);
		else if (str[i] == '\'' || str[i] == '"')
			add_pretoken(&pretokens, get_quoted(str, &i), WORD);
		else
			add_pretoken(&pretokens, get_word(str, &i), WORD);
	}
	return (pretokens);
}
