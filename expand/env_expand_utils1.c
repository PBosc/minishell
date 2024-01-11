/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:36:22 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 00:37:01 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_emptyquote_next(t_pretoken *pretoken)
{
	if (!pretoken->next_pretoken)
		return (0);
	if (!ft_strcmp(pretoken->next_pretoken->content, "''")
		|| !ft_strcmp(pretoken->next_pretoken->content, "\"\""))
		return (1);
	return (0);
}

char	*get_name(char *str, int *ptr_i)
{
	char	*name;
	int		len;
	int		j;

	len = 0;
	while (str[*ptr_i + len] && str[*ptr_i + len] != '$')
		len++;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	j = 0;
	while (j < len)
	{
		name[j] = str[*ptr_i];
		j++;
		*ptr_i = *ptr_i + 1;
	}
	name[j] = 0;
	return (name);
}
