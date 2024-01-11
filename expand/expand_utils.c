/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:37:58 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/11 00:38:56 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name_dq(char *str, int *ptr_i)
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

void	a(int *i, int *j)
{
	*i = *i + 1;
	*j = *j + 1;
}
