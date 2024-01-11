/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:53:09 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 03:42:06 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_putcharbis(char c, int *length, int fd)
{
	write(fd, &c, 1);
	*length = *length + 1;
}

void	ft_putstrbis(char *str, int *length, int fd)
{
	int	i;

	if (!str)
	{
		write(fd, "(null)", 6);
		*length = *length + 6;
		return ;
	}
	i = 0;
	while (str[i])
	{
		write(fd, str + i, 1);
		*length = *length + 1;
		i++;
	}
}

void	ft_putptrhexabis(uintptr_t ptr, int *length, int fd)
{
	if (!ptr)
	{
		write(fd, "(nil)", 5);
		*length = *length + 5;
		return ;
	}
	write(fd, "0x", 2);
	*length = *length + 2;
	ft_putnbrbasebis(ptr, 16, length, fd);
}

void	ft_putnbrdecabis(int n, int *length, int fd)
{
	if (n == -2147483648)
	{
		write(2, "-2147483648", 11);
		*length = *length + 11;
		return ;
	}
	if (n < 0)
	{
		ft_putcharbis('-', length, fd);
		n *= -1;
	}
	ft_putnbrbasebis(n, 10, length, fd);
}
