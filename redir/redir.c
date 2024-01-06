/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:21:46 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/06 00:17:24 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_fd_in(t_redir_list *redirs)
{
	t_redir_list	*redir;
	char			*infile;

	redir = redirs;
	infile = NULL;
	while (redir)
	{
		if (redir->type == R_IN)
			infile = redir->file;
		redir = redir->next_redir;
	}
	if (infile)
		return (open(infile, O_RDONLY));
	return (STDIN_FILENO);
}

int	get_fd_out(t_redir_list *redirs)
{
	t_redir_list	*redir;
	char			*outfile;

	redir = redirs;
	outfile = NULL;
	while (redir)
	{
		if (redir->type == R_OUT)
			outfile = redir->file;
		redir = redir->next_redir;
	}
	if (outfile)
		return (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (STDOUT_FILENO);
}

void	get_redirs(t_redir_list *redirs, t_exec *data)
{
	data->fd_in = get_fd_in(redirs);
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