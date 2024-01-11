/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:30:05 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 00:30:56 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

t_pretoken	*added_whitespace(t_pretoken *pretoken)
{
	t_pretoken	*new;

	new = malloc(sizeof(t_pretoken));
	if (!new)
		return (pretoken);
	new->content = ft_strdup(" ");
	new->type = WHITESPACE;
	new->next_pretoken = pretoken;
	return (new);
}

void	add_first_one(t_pretoken *pretoken, char **splitted, int *i)
{
	pretoken->content = splitted[*i];
	if (splitted[*i + 1])
		pretoken->next_pretoken = added_whitespace(pretoken->next_pretoken);
	*i = *i + 1;
}

void	split_expand(char *res, t_pretoken *pretoken)
{
	char		**splitted;
	int			i;
	t_pretoken	*new;
	t_pretoken	*tmp;

	splitted = ft_split(res, ' ');
	if (!splitted)
		return ;
	i = 0;
	add_first_one(pretoken, splitted, &i);
	tmp = pretoken->next_pretoken;
	while (splitted[i])
	{
		new = new_pretoken(splitted[i], WORD);
		if (!new)
			return ;
		if (splitted[i + 1])
			new->next_pretoken = added_whitespace(tmp->next_pretoken);
		else
			new->next_pretoken = tmp->next_pretoken;
		tmp->next_pretoken = new;
		tmp = new;
		i++;
	}
	free(splitted);
}
