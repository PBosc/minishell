/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:03:41 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/09 21:28:57 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_not_found(t_node_ast *node)
{
	g_status = 127;
	if (!node->args[0])
		return (g_status);
	dprintf(2, "minishell: %s: %s\n", node->args[0], strerror(errno));
	return (1);
}

int	handle_nocmd_heredoc(t_exec *data)
{
	t_hered	*heredoc;

	heredoc = NULL;
	if (data->fd_in == REDIR_HEREDOC)
	{
		read_here_doc(&heredoc, data);
		free_heredoc(heredoc);
	}
	g_status = 0;
	return (1);
}

int	precheck(t_node_ast *node, t_exec *data, t_minishell *minishell)
{
	if (data->is_pipe)
		return (exec_pipe(node, data, 0, minishell), 0);
	if (!get_redirs(node->redirs, data))
		return (1);
	if (!node->args)
		return (handle_nocmd_heredoc(data));
	if (pipe(data->pipe) == -1)
		return (EXIT_FAILURE);
	if (!is_builtin(node->args[0]))
		node->args[0] = get_valid_path(get_path(data->env), node->args[0]);
	if (node->args[0] == NULL
		|| (!is_builtin(node->args[0])
			&& access(node->args[0], F_OK | X_OK) == -1))
		return (handle_not_found(node));
	if (is_builtin(node->args[0]))
		return (exec_builtin(node->args, minishell), 0);
	return (0);
}

int	child_pipes(t_exec *data, int is_end)
{
	if (data->fd_in != STDIN_FILENO && data->fd_in != REDIR_HEREDOC)
		dup2(data->fd_in, STDIN_FILENO);
	else if (data->prev_pipe != -1)
		dup2(data->prev_pipe, STDIN_FILENO);
	if (is_end)
	{
		if (data->fd_out != STDOUT_FILENO)
			dup2(data->fd_out, STDOUT_FILENO);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	close(data->pipe[0]);
	return (EXIT_SUCCESS);
}

int	pipe_precheck(t_node_ast *node, t_exec *data)
{
	if (!get_redirs(node->redirs, data))
		return (1);
	if (!node->args)
	{
		if (data->fd_in == REDIR_HEREDOC)
			init_heredoc(data);
		g_status = 0;
		return (1);
	}
	if (data->fd_in == REDIR_HEREDOC)
		init_heredoc(data);
	if (!is_builtin(node->args[0]))
		node->args[0] = get_valid_path(get_path(data->env), node->args[0]);
	if (node->args[0] == NULL
		|| (!is_builtin(node->args[0])
			&& access(node->args[0], F_OK | X_OK) == -1))
	{
		handle_not_found(node);
		close(data->pipe[0]);
		close(data->pipe[1]);
		return (1);
	}
	if (pipe(data->pipe) == -1)
		return (1);
	return (0);
}
