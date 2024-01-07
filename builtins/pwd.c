/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:46:09 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/06 23:12:07 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int    pwd(char **args, t_minishell *minishell)
{
    char buf[2048];

    (void)args;
    (void)minishell;
    if (!getcwd(buf, 2048))
        return (ft_dprintf(2, "bash : pwd: %s\n", /*errno*/""), 1);
    printf("%s\n", buf);
    return (0);
}
