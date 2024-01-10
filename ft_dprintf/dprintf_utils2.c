/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:36:51 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:46:21 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	match_mix(int mix, int *maj, uintptr_t *base)
{
	if (mix == 10)
	{
		*maj = 0;
		*base = 10;
	}
	else if (mix == 11)
	{
		*maj = 1;
		*base = 10;
	}
	else if (mix == 16)
	{
		*maj = 0;
		*base = 16;
	}
	else if (mix == 17)
	{
		*maj = 1;
		*base = 16;
	}
}

void	ft_putnbrbasebis(uintptr_t n, int mix, int *length, int fd)
{
	char		*b;
	int			maj;
	uintptr_t	base;

	match_mix(mix, &maj, &base);
	b = "0123456789abcdef0123456789ABCDEF";
	if (n > base - 1)
		ft_putnbrbasebis(n / base, mix, length, fd);
	ft_putcharbis(b[maj * base + n % base], length, fd);
}
