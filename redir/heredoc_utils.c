/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:22:53 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/13 21:23:25 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_limit(char *line, char *limiter)
{
	int	length;

	length = ft_strlen(limiter);
	if (line[0] == '\n')
		return (0);
	return (ft_strncmp(line, limiter, length) == 0 && (line[length] == '\n'));
}

void	free_heredoc(t_hered *here_doc)
{
	t_hered	*tmp;

	while (here_doc)
	{
		tmp = here_doc;
		here_doc = here_doc->next;
		free(tmp->line);
		free(tmp);
	}
}

t_hered	*ft_hered_last(t_hered *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

int	ft_lstpush_back(t_hered **lst, char *line)
{
	t_hered	*new;

	new = malloc(sizeof(t_hered));
	if (!new)
		return (0);
	new->line = ft_strdup(line);
	new->next = NULL;
	if (lst)
	{
		if (*lst)
			ft_hered_last(*lst)->next = new;
		else
			*lst = new;
	}
	return (1);
}

void	garbage_collector(t_minishell *minishell, t_hered **here_doc, int i)
{
	static t_minishell	*ms = NULL;
	static t_hered		**heredoc = NULL;

	if (i)
	{
		free_heredoc(*heredoc);
		clear_ast(&ms->ast);
		clear_env(&(ms->env));
		free(ms);
	}
	else
	{
		ms = minishell;
		heredoc = here_doc;
	}
}
