/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:34:16 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:49:45 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	str = malloc(sizeof(char) * (ft_intlen(n) + 1));
	if (!str)
		return (NULL);
	while (n > 9)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	str[i++] = n + '0';
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}
