/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:12:44 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/01 15:17:02 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parsing.h"

typedef struct s_exec {
	int status;
	int wpid;
	int pid;
	int fd[2];
	int fd_in;
	int fd_out;
	int ret_value;
} t_exec;

typedef int (*t_fct_ptr)(t_node_ast *, t_exec *);

//exec operations
int    exec_and(t_node_ast *node, t_exec *exec);
int    exec_or(t_node_ast *node, t_exec *exec);
int    exec_pipe(t_node_ast *node, t_exec *exec);
int    exec_semicolon(t_node_ast *node, t_exec *exec);
int    exec_redirect_in(t_node_ast *node, t_exec *exec);
int    exec_redirect_out(t_node_ast *node, t_exec *exec);
int    exec_redirect_append(t_node_ast *node, t_exec *exec);
int    exec_heredoc(t_node_ast *node, t_exec *exec);
int    exec_nothing(t_node_ast *node, t_exec *exec);

//actual execution
int   exec_cmd(t_node_ast *node, t_exec *exec);
static int	wait_commands(t_exec *exec);
int		exec(t_node_ast *ast, t_exec *exec);

#endif