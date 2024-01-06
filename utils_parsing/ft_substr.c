/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 02:27:57 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 02:46:57 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*empty(void)
{
	char	*err;

	err = malloc(1);
	if (!err)
		return (NULL);
	err[0] = 0;
	return (err);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > (unsigned int)length)
		return (empty());
	if (len > length - start)
		len = length - start;
	if (!len)
		return (NULL);
	res = (char *)malloc((len + 1) * sizeof(*s));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > (unsigned int)length)
		return (empty());
	if (len > length - start)
		len = length - start;
	res = (char *)malloc((len + 1) * sizeof(*s));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	free(s);
	return (res);
}
