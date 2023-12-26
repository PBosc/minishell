/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:19:13 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/26 16:02:36 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int check_quotes(char *str)
{
    int i;
    char c;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            c = str[i];
            while (str[++i] && str[i] != c)
                i++;
            if (!str[i])
                return (0); 
            i++;
        }
        else
            i++;
    }
    return (1);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s2[i] && (s1[i] == s2[i]))
        i++;
    return (s1[i] - s2[i]);
}
