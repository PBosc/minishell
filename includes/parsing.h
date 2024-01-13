/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:52:56 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/13 16:18:44 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ft_dprintf.h"
# include <dirent.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
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
	int					wild;
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

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next_env;
}						t_env;

typedef struct s_minishell
{
	char				*cmd_line;
	t_env				*env;
	t_pretoken			*pretokens;
	t_token				*tokens;
	t_node_ast			*ast;
	int					exit_status;
}						t_minishell;

/*Parser*/
t_node_ast				*parser(t_token *tokens);

/*Token builders*/
t_pretoken				*pretokenization(char *str);
t_token					*tokenization(t_pretoken *pretokens);
t_token					*last_token(t_token *token);
int						new_token(t_token **tokens, char *content,
							t_token_type type);

/*Syntax checker*/
int						check_syntax(t_pretoken *pretokens);
void					syntax_error(t_pretoken *pretoken);

/*Expand functions*/
char					*rm_quotes(char *str);
void					expand_env(t_pretoken *pretoken,
							t_minishell *minishell);
void					expand_env_dq(t_pretoken *pretoken,
							t_minishell *minishell);
void					expand_wildcard(t_pretoken *pretoken);
void					expand_pretokens(t_pretoken *pretokens,
							t_minishell *minishell);
char					*get_env(char *key, t_env *env);
int						has_whitespace(char *str);
t_pretoken				*added_whitespace(t_pretoken *pretoken);
void					add_first_one(t_pretoken *pretoken, char **splitted,
							int *i);
void					split_expand(char *res, t_pretoken *pretoken);
int						is_emptyquote_next(t_pretoken *pretoken);
char					*get_name(char *str, int *ptr_i);
char					*get_name_dq(char *str, int *ptr_i);
void					a(int *i, int *j);
int						get_len(char *str, int i);

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
char					*char_to_string(char c, int *i);
int						is_whitespace(char c);
char					*get_whitespace(char *str, int *i);
char					*get_operator(char *str, int *i);
char					*get_redir(char *str, int *i);
char					*get_quoted(char *str, int *i);
int						is_in_charset(char c, char *set);
char					*get_word(char *str, int *i);
t_pretoken				*skip_spaces(t_pretoken *pretokens);
t_pretoken				*new_pretoken(char *content, t_pretoken_type type);
void					update_env(char *key, char *value, t_env *env);
void					delete_env(char *key, t_env *env,
							t_minishell *minishell);
t_env					*new_env(char *key, char *value, int i);
char					*get_name(char *str, int *ptr_i);
void					display_env(t_env *env);
char					*ft_itoa(int n);
int						check_and(char *str);
int						check_quotes(char *str);
char					**sort_tab(char **tab);
int						plen(char **map);

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
int						ft_isatoi(char *str);
int						ft_atoi(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_isalpha(int c);
void					*ft_memset(void *s, int c, size_t n);
char					*ft_strjoin_free2(char *s1, char *s2);

/*Free and error handling functions*/
void					clear_pretokens(t_pretoken **pretokens);
void					clear_tokens(t_token **tokens);
void					clear_tab(char **tab);
void					clear_redirs(t_redir_list **redirs);
void					clear_env(t_env **env);
void					clear_ast(t_node_ast **ast);
void					move_def(t_pretoken **pretoken, int i);
void					move_def_token(t_token **token, int i);

/*Debugging*/
void					display_tab(char **tab);
void					display_pretokens(t_pretoken *pretoken);

#endif