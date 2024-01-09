/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:19:55 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 05:55:08 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void	clear_pretokens(t_pretoken **pretokens)
{
	t_pretoken	*tmp;

	if (!pretokens || !*pretokens)
		return ;
	while (*pretokens)
	{
		tmp = (*pretokens)->next_pretoken;
		free((*pretokens)->content);
		free(*pretokens);
		*pretokens = tmp;
	}
}

void	clear_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next_token;
		free((*tokens)->content);
		free(*tokens);
		*tokens = tmp;
	}
}

void	clear_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clear_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next_env;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

void	clear_redirs(t_redir_list **redirs)
{
	t_redir_list	*tmp;

	if (!redirs || !*redirs)
		return ;
	while (*redirs)
	{
		tmp = (*redirs)->next_redir;
		free((*redirs)->file);
		free(*redirs);
		*redirs = tmp;
	}
}

void	clear_ast(t_node_ast **ast)
{
	t_node_ast *tmp_l;
	t_node_ast *tmp_r;
	if (!ast || !*ast)
		return ;
	tmp_l = (*ast)->left_child;
	tmp_r = (*ast)->right_child;
	if ((*ast)->type == T_CMD)
	{
		clear_tab((*ast)->args);
		clear_redirs(&((*ast)->redirs));
	}
	free(*ast);
	clear_ast(&tmp_l);
	clear_ast(&tmp_r);
}

void	move_def(t_pretoken **pretoken, int i)
{
	t_pretoken *tmp;
	
	tmp = (*pretoken)->next_pretoken;
	if (i)
		free((*pretoken)->content);
	free(*pretoken);
	*pretoken = tmp;
}

void	move_def_token(t_token **token, int i)
{
	t_token *tmp;
	
	tmp = (*token)->next_token;
	if (i)
		free((*token)->content);
	free(*token);
	*token = tmp;
}
