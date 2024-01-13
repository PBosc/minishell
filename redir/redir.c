/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:21:46 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 23:35:55 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_infile(t_redir_list *redir, t_exec *data,
		char **infile, t_minishell *minishell)
{
	t_hered	*heredoc;

	heredoc = NULL;
	if (data->is_here_doc == 1
		&& (redir->type == R_HEREDOC || redir->type == R_IN))
	{
		init_heredoc(data, minishell, 1);
	}
	if (redir->type == R_IN)
	{
		*infile = redir->file;
		data->is_here_doc = 0;
	}
	if (redir->type == R_HEREDOC)
	{
		*infile = redir->file;
		data->limiter = redir->file;
		data->is_here_doc = 1;
	}
	return (data->is_here_doc);
}

int	get_outfile(t_redir_list *redir, char **outfile)
{
	int				is_append;
	int				fd;

	is_append = 0;
	if (redir->type == R_OUT)
	{
		*outfile = redir->file;
		is_append = 0;
	}
	if (redir->type == R_APPEND)
	{
		*outfile = redir->file;
		is_append = 1;
	}
	if (*outfile)
	{
		fd = open(*outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_close(fd);
	}
	return (is_append);
}

int	get_fd_in(t_redir_list *redirs, t_exec *data,
		char **infile, t_minishell *minishell)
{
	t_redir_list	*redir;

	*infile = NULL;
	data->is_here_doc = 0;
	redir = redirs;
	while (redir)
	{
		get_infile(redir, data, infile, minishell);
		redir = redir->next_redir;
	}
	if (data->is_here_doc && *infile)
		return (REDIR_HEREDOC);
	if (*infile)
		return (open(*infile, O_RDONLY));
	return (STDIN_FILENO);
}

int	get_fd_out(t_redir_list *redirs, char **outfile)
{
	t_redir_list	*redir;
	int				is_append;

	redir = redirs;
	*outfile = NULL;
	is_append = 0;
	while (redir)
	{
		is_append = get_outfile(redir, outfile);
		redir = redir->next_redir;
	}
	if (is_append && *outfile)
		return (open(*outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (*outfile)
		return (open(*outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (STDOUT_FILENO);
}

int	get_redirs(t_redir_list *redirs, t_exec *data, t_minishell *minishell)
{
	char	*infile;
	char	*outfile;

	data->fd_in = get_fd_in(redirs, data, &infile, minishell);
	if (data->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			infile, strerror(errno));
		g_status = 1;
		return (0);
	}
	data->fd_out = get_fd_out(redirs, &outfile);
	if (data->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			outfile, strerror(errno));
		g_status = 1;
		return (0);
	}
	return (1);
}
