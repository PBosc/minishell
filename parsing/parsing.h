/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:52:56 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/26 16:56:38 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../token/token.h"

typedef struct s_node_ast
{
    char *str;
    t_token *token;
    struct s_node_ast *left_child;
    struct s_node_ast *right_child;
} t_node_ast;

#endif