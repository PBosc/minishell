/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretoken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 04:29:19 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:48:06 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*char_to_string(char c, int *i)
{
	char	*res;

	res = malloc(2);
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = 0;
	*i = *i + 1;
	return (res);
}

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*get_whitespace(char *str, int *i)
{
	char	*res;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (str[*i + len] && is_whitespace(str[*i + len]))
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (j < len)
	{
		res[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	res[j] = 0;
	return (res);
}

char	*get_operator(char *str, int *i)
{
	char	*res;

	res = malloc(3);
	if (!res)
		return (NULL);
	res[0] = str[*i];
	res[1] = str[*i + 1];
	res[2] = 0;
	*i = *i + 2;
	return (res);
}

char	*get_redir(char *str, int *i)
{
	char	*res;

	if ((str[*i] == '>' && str[*i + 1] != '>') || (str[*i] == '<' && str[*i
				+ 1] != '<'))
	{
		return (char_to_string(str[*i], i));
	}
	res = malloc(3);
	if (!res)
		return (NULL);
	res[0] = str[*i];
	res[1] = str[*i + 1];
	res[2] = 0;
	*i = *i + 2;
	return (res);
}
