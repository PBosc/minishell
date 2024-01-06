/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 00:50:04 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/06 16:06:59 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
	TODO CA MARCHE PAS LES QUOTES ATTENTION
*/

int	check_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
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

void	add_pretoken(t_pretoken **pretoken, char *content, t_pretoken_type TYPE, int *led)
{
	t_pretoken	*new;
	t_pretoken	*last;

	if (!content)
	{
		*led = 0;
		return ;
	}
	last = last_pretoken(*pretoken);
	new = malloc(sizeof(t_pretoken));
	if (!new)
	{
		free(content);
		*led = 0;
		return ;
	}
	new->content = content;
	new->type = TYPE;
	new->next_pretoken = NULL;
	if (!(*pretoken))
		*pretoken = new;
	else
		last->next_pretoken = new;
}

int	match_pretokens(t_pretoken **pretokens, char *str, int *i)
{
	int	led;

	led = 1;
	if (str[*i] == '(')
		add_pretoken(pretokens, char_to_string(str[*i], i), OPEN_PAR, &led);
	else if (str[*i] == ')')
		add_pretoken(pretokens, char_to_string(str[*i], i), CLOSED_PAR, &led);
	else if (is_whitespace(str[*i]))
		add_pretoken(pretokens, get_whitespace(str, i), WHITESPACE, &led);
	else if (str[*i] == '|' && str[*i + 1] != '|')
		add_pretoken(pretokens, char_to_string(str[*i], i), PIPE, &led);
	else if (str[*i] == '|' && str[*i + 1] == '|')
		add_pretoken(pretokens, get_operator(str, i), OPERATOR, &led);
	else if (str[*i] == '&' && str[*i + 1] == '&')
		add_pretoken(pretokens, get_operator(str, i), OPERATOR, &led);
	else if (str[*i] == '>' || str[*i] == '<')
		add_pretoken(pretokens, get_redir(str, i), REDIR, &led);
	else if (str[*i] == '\'' || str[*i] == '"')
		add_pretoken(pretokens, get_quoted(str, i), WORD, &led);
	else
		add_pretoken(pretokens, get_word(str, i), WORD, &led);
	return (led);
}

t_pretoken	*pretokenization(char *str)
{
	t_pretoken	*pretokens;
	int			i;

	i = 0;
	if (!str)
		return (NULL);
	// if (!check_quotes(str))
	// 	return (ft_dprintf(2, "minishell: syntax error because of unclosed quote\n"), NULL);
	pretokens = NULL;
	while (str[i])
	{
		if (!match_pretokens(&pretokens, str, &i))
			return (clear_pretokens(&pretokens), NULL);
	}
	return (pretokens);
}
