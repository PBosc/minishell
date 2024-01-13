/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:12:44 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 17:20:54 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

# define REDIR_HEREDOC -42
# define BUFFER_SIZE 1

typedef struct s_exec
{
	int				status;
	int				wpid;
	int				pid;
	int				pipe[2];
	int				fd_in;
	int				fd_out;
	int				ret_value;
	int				prev_pipe;
	t_env			*env;
	int				is_pipe;
	char			*limiter;
	t_minishell		*minishell;
	int				is_here_doc;
}					t_exec;

typedef struct s_hered
{
	char			*line;
	struct s_hered	*next;
}					t_hered;

typedef int			(*t_fct_ptr)(t_node_ast *, t_exec *, t_minishell *);

// exec operations
int					exec_and(t_node_ast *node, t_exec *exec,
						t_minishell *minishell);
int					exec_or(t_node_ast *node, t_exec *exec,
						t_minishell *minishell);
void				exec_pipeline(t_node_ast *node, t_exec *exec,
						t_minishell *minishell);

// actual execution
int					exec_cmd(t_node_ast *node, t_exec *exec,
						t_minishell *minishell);
int					wait_commands(t_exec *exec);
int					exec(t_node_ast *ast, t_exec *exec, t_minishell *minishell);
void				exec_pipe(t_node_ast *node, t_exec *data, int is_end,
						t_minishell *minishell);

// path
char				*get_valid_path(char **paths, char *cmd);
void				free_tab_2d(char **tab);
int					starts_with(char *str, char *start);
char				*ft_trim(char *str, int start);
char				**get_path(t_env *env);
char				**tab_env(t_env *env);

// utils
char				**ft_split(char const *s, char c);
char				*get_next_line(int fd);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_putstr_fd(char *s, int fd);
char				*get_name(char *str, int *ptr_i);
void				ft_close(int fd);
void				garbage_collector(t_minishell *minishell,
						t_hered **here_doc, int i);

// pipe
int					exec_master_pipe(t_node_ast *node, t_exec *data,
						t_minishell *minishell);

// init

void				init_data(t_exec *data, t_env *env);

// redirections

int					get_redirs(t_redir_list *redirs, t_exec *data,
						t_minishell *minishell);
int					read_here_doc(t_hered **here_doc, t_exec *data,
						t_minishell *minishell);
int					write_here_doc(t_hered *here_doc, t_exec *data);
int					init_heredoc(t_exec *data, t_minishell *minishell,
						int ignore_fork);
void				free_heredoc(t_hered *here_doc);
int					is_limit(char *line, char *limiter);
t_hered				*ft_hered_last(t_hered *lst);
int					ft_lstpush_back(t_hered **lst, char *line);

// builtins

int					cd(char **args, t_minishell *minishell);
int					echo(char **tab);
int					env(t_minishell *minishell);
int					exit_minishell(char **args, t_minishell *minishell);
int					export(char **args, t_minishell *minishell);
int					pwd(char **args, t_minishell *minishell);
int					unset(char **args, t_minishell *minishell);
int					is_builtin(char *cmd);
int					exec_builtin(char **args, t_minishell *minishell,
						t_exec *data);

// handlers

int					handle_not_found(t_node_ast *node);
int					handle_nocmd_heredoc(t_exec *data, t_minishell *minishell);
int					precheck(t_node_ast *node, t_exec *data,
						t_minishell *minishell);
int					pipe_precheck(t_node_ast *node, t_exec *data,
						t_minishell *minishell);
int					child_pipes(t_exec *data, int in_end);
void				fork_sig_handler(int sig);
void				heredoc_sig_handler(int sig);
char				*expanded_heredoc(char *str, t_minishell *minishell);
void				close_pipes(t_exec *data);
int					id(char *path);

#endif