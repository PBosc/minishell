/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:52:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 03:01:32 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <dirent.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_pretoken_type
{
	WORD,
	WHITESPACE,
	PIPE,
	REDIR,
	OPERATOR,
	OPEN_PAR,
	CLOSED_PAR,
}						t_pretoken_type;

typedef enum e_token_type
{
	OPERAND,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	REDIRECT_APPEND,
	PIPEPIPE,
	OPEN_P,
	CLOSED_P,
	AND,
	OR
}						t_token_type;

typedef enum e_node_type
{
	T_CMD,
	T_PIPE,
	T_OR,
	T_AND
}						t_node_type;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}						t_redir_type;

typedef struct s_pretoken
{
	char				*content;
	t_pretoken_type		type;
	struct s_pretoken	*next_pretoken;
}						t_pretoken;

typedef struct s_token
{
	char				*content;
	t_token_type		type;
	struct s_token		*next_token;
}						t_token;

typedef struct s_redir_list
{
	t_redir_type		type;
	char				*file;
	struct s_redir_list	*next_redir;
}						t_redir_list;

typedef struct s_node_ast
{
	t_node_type			type;
	char				**args;
	struct s_redir_list	*redirs;
	struct s_node_ast	*left_child;
	struct s_node_ast	*right_child;
}						t_node_ast;

/*Parser*/
t_node_ast				*parser(t_token *tokens);

/*Token builders*/
t_pretoken				*pretokenization(char *str);
t_token					*tokenization(t_pretoken *pretokens);

/*Syntax checker*/
int						check_syntax(t_pretoken *pretokens);

/*Expand functions*/
void					rm_quotes(t_pretoken *pretoken);
void					expand_env(t_pretoken *pretoken);
void					expand_wildcard(t_pretoken *pretoken);
void					expand_pretokens(t_pretoken *pretokens);

/*Redirections*/
int						add_redir(t_node_ast *node, t_token **token);
t_redir_list			*create_redir(t_redir_type type, char *file);
void					add_last_redir(t_redir_list **redirs,
							t_redir_list *new);

/*Automata*/
int						q0(t_pretoken *pretokens, int i);
int						q1(t_pretoken *pretokens, int i);
int						q2(t_pretoken *pretokens, int i);
int						q3(t_pretoken *pretokens, int i);
int						q4(t_pretoken *pretokens, int i);
int						q5(t_pretoken *pretokens, int i);

/*Utils*/
int						is_operator(t_token *token);
int						is_redir(t_token *token);
int						get_precedence(t_token_type type);
t_node_ast				*create_node(t_node_type type);
char					**join_tab(char **tab, char *str);
t_node_type				get_type(t_token_type type);
char					*char_to_string(char c);
int						is_whitespace(char c);
char					*get_whitespace(char *str, int *i);
char					*get_operator(char *str, int *i);
char					*get_redir(char *str, int *i);
char					*get_quoted(char *str, int *i);
int						is_in_charset(char c, char *set);
char					*get_word(char *str, int *i);
t_pretoken				*skip_spaces(t_pretoken *pretokens);

/*Libft functions*/
char					*ft_strchr(char *s, char c);
int						ft_strchri(char *s, char c);
char					*ft_strdup(char *s);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strjoin_free(char *s1, char *s2);
char					*ft_substr(char *s, unsigned int start, size_t len);
char					*ft_substr_free(char *s, unsigned int start,
							size_t len);
int						ft_strlen(char *str);
int						ft_isalnum(int c);
int						ft_strcmp(const char *s1, const char *s2);
void					*ft_calloc(size_t nmemb, size_t size);
size_t					ft_strlcpy(char *dst, char *src, size_t size);

#endif