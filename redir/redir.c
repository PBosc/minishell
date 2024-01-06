/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:21:46 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/06 17:54:50 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_fd_in(t_redir_list *redirs, t_exec *data)
{
	t_redir_list	*redir;
	char			*infile;
	int				is_here_doc;

	redir = redirs;
	infile = NULL;
	is_here_doc = 0;
	while (redir)
	{
		if (redir->type == R_IN)
		{
			infile = redir->file;
			is_here_doc = 0;
		}
		if (redir->type == R_HEREDOC)
		{
			infile = redir->file;
			data->limiter = redir->file;
			is_here_doc = 1;
		}
		redir = redir->next_redir;
	}
	if (is_here_doc && infile)
		return (REDIR_HEREDOC);
	if (infile)
		return (open(infile, O_RDONLY));
	return (STDIN_FILENO);
}

int	get_fd_out(t_redir_list *redirs)
{
	t_redir_list	*redir;
	char			*outfile;
	int				is_append;

	redir = redirs;
	outfile = NULL;
	is_append = 0;
	while (redir)
	{
		if (redir->type == R_OUT)
		{
			outfile = redir->file;
			is_append = 0;
		}
		if (redir->type == R_APPEND)
		{
			outfile = redir->file;
			is_append = 1;
		}
		redir = redir->next_redir;
	}
	if (is_append && outfile)
		return (open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (outfile)
		return (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (STDOUT_FILENO);
}

void	get_redirs(t_redir_list *redirs, t_exec *data)
{
	data->fd_in = get_fd_in(redirs, data);
	if (data->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			redirs->file);
		g_status = 1;
		return ;
	}
	data->fd_out = get_fd_out(redirs);
	if (data->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			redirs->file);
		g_status = 1;
		return ;
	}
}
