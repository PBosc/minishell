/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:56:35 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:45:44 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_match(char c, va_list *parameters, int *length, int fd)
{
	if (c == 'i' || c == 'd')
		return (ft_putnbrdecabis(va_arg(*parameters, int), length, fd));
	if (c == 'u')
		return (ft_putnbrbasebis(va_arg(*parameters, unsigned int), 10, length,
				fd));
	if (c == 'c')
		return (ft_putcharbis(va_arg(*parameters, int), length, fd));
	if (c == 's')
		return (ft_putstrbis(va_arg(*parameters, char *), length, fd));
	if (c == 'p')
		return (ft_putptrhexabis((uintptr_t)va_arg(*parameters, void *), length,
				fd));
	if (c == 'x')
		return (ft_putnbrbasebis(va_arg(*parameters, unsigned int), 16, length,
				fd));
	if (c == 'X')
		return (ft_putnbrbasebis(va_arg(*parameters, unsigned int), 17, length,
				fd));
	if (c == '%')
		return (ft_putcharbis('%', length, fd));
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		i;
	int		length;
	va_list	parameters;

	va_start(parameters, str);
	i = 0;
	length = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '%')
		{
			write(fd, str + i, 1);
			length++;
			i++;
		}
		if (str[i] == '%' && str[i + 1])
			ft_match(str[++i], &parameters, &length, fd);
		if (str[i])
			i++;
	}
	va_end(parameters);
	return (length);
}
