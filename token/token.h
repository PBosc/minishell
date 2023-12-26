/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:38:23 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/26 18:36:57 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef enum
{
	OPERAND,
    ARGUMENT,
	OPERATOR,
	REDIRECTION,
	HEREDOC
}					e_token_type;

typedef enum
{
	AND,
	OR,
	PIPE,
	SEMICOLON,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC_MARKER,
	NOTHING
}					e_operator_type;

//struct s_token;

typedef struct s_token
{
	char *	content;
	e_token_type	type;
	e_operator_type	ope_type;
    struct s_token  *prev_token;
	struct s_token	*next_token;
}					t_token;


int ft_strcmp(char *s1, char *s2);
char	**ft_split(char *s, char c);
int check_quotes(char *str);

#endif
