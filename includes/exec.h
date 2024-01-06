/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:12:44 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/06 23:14:06 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# define REDIR_HEREDOC -42
# define BUFFER_SIZE 1024

typedef struct s_exec {
	int		status;
	int		wpid;
	int		pid;
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	int		ret_value;
	int		prev_pipe;
	char	**env;
	int 	is_pipe;
	char	*limiter;
}	t_exec;

typedef struct s_hered {
	char			*line;
	struct s_hered	*next;
}	t_hered;

typedef int	(*t_fct_ptr)(t_node_ast *, t_exec *);

//exec operations
int		exec_and(t_node_ast *node, t_exec *exec);
int		exec_or(t_node_ast *node, t_exec *exec);
void	exec_pipeline(t_node_ast *node, t_exec *exec);

//actual execution
int		exec_cmd(t_node_ast *node, t_exec *exec);
int		wait_commands(t_exec *exec);
int		exec(t_node_ast *ast, t_exec *exec);

//path
char	*get_valid_path(char **paths, char *cmd);
void	free_tab_2d(char **tab);
int		starts_with(char *str, char *start);
char	*ft_trim(char *str, int start);
char	**get_path(char **env);

//utils
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_putstr_fd(char *s, int fd);
char	*get_name(char *str, int *ptr_i);

//pipe
int		exec_master_pipe(t_node_ast *node, t_exec *data);

//init

void	init_data(t_exec *data, char **env);

//redirections

void	get_redirs(t_redir_list *redirs, t_exec *data);
int		read_here_doc(t_hered **here_doc, t_exec *data);
int		write_here_doc(t_hered *here_doc, t_exec *data);
int		init_heredoc(t_exec *data);

#endif