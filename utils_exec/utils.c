/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:27:07 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/07 03:58:28 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((unsigned char)s1[i]
// 		&& (unsigned char)s1[i] == (unsigned char)s2[i] && i < n)
// 		i++;
// 	if (i < n)
// 		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	return (0);
// }

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	else
		write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}
