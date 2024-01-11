/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:09 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 23:01:50 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **args, t_minishell *minishell)
{
	char	buf[2048];

	(void)args;
	(void)minishell;
	if (!getcwd(buf, 2048))
		return (ft_dprintf(2, "minishell : pwd: %s\n", strerror(errno)), 1);
	printf("%s\n", buf);
	return (0);
}
