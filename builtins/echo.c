/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:45:58 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:29:36 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	echo(char **tab)
{
	int	led;
	int	i;

	if (!tab || !*tab)
		return (0);
	led = 0;
	i = 0;
	if (!ft_strcmp(tab[i], "-n"))
	{
		led = 1;
		i++;
	}
	while (tab[i])
	{
		if (!tab[i + 1])
			printf("%s", tab[i]);
		else
			printf("%s ", tab[i]);
		i++;
	}
	if (!led)
		printf("\n");
	return (0);
}
