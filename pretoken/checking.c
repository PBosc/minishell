/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 01:27:30 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/12 01:43:54 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && str[i + 1] != '&')
			return (0);
		else if (str[i] == '&' && str[i + 1] == '&')
			i = i + 2;
		else
			i++;
	}
	return (1);
}

int	check_quotes(char *str)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		i++;
	}
	return (!single_quote && !double_quote);
}
