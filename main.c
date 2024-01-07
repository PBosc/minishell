/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:54:26 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/07 00:07:19 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"
#include "minishell.h"

void	display_pretokens(t_pretoken *pretoken)
{
	int	a;

	while (pretoken)
	{
		a = pretoken->type;
		printf("TOKEN %s OF TYPE %d\n", pretoken->content, a);
		pretoken = pretoken->next_pretoken;
	}
	printf("ADRESS %p\n\n", pretoken);
}

void	display_tokens(t_token *token)
{
	int	a;

	if (!token)
		printf("ups\n");
	while (token)
	{
		a = token->type;
		printf("TOKEN %s OF TYPE %d\n      |\n", token->content, a);
		token = token->next_token;
	}
}

#define COUNT 10

void display_tab(char **tab)
{
	int i = 0;
	
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("%s, ", tab[i]);
		i++;
	}
}

void display_redir(t_redir_list *redirs)
{
	if (!redirs)
		return ;
	while (redirs)
	{
		printf("%s, ", redirs->file);
		redirs = redirs->next_redir;
	}
}

void	printutil(t_node_ast *root, int space)
{
	int	a;
	int	i;

	if (root == NULL)
		return ;
	space += COUNT;
	printutil(root->right_child, space);
	printf("\n");
	i = COUNT;
	while (i < space)
	{
		printf(" ");
		i++;
	}
	a = root->type;
	printf("%d, ", a);
	if (!a)
	{
		display_tab(root->args);
		display_redir(root->redirs);
	}
	printutil(root->left_child, space);
}

void	display_ast(t_node_ast *root)
{
	printutil(root, 0);
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	t_minishell *minishell;
	t_exec		data;
	//char		*str;
	//t_pretoken	*pretokens;
	//t_token		*tokens;
	//t_node_ast	*ast;

	(void)ac;
	(void)av;
	g_status = 0;
	minishell = ft_calloc(1, sizeof(minishell));
	if (!minishell)
		return (1);
	while (1)
	{
		minishell->cmd_line = readline("minishell$ ");
		if (!minishell->cmd_line)
			continue ;
		if (*minishell->cmd_line)
			add_history(minishell->cmd_line);
		if (!ft_strcmp(minishell->cmd_line, "exit"))
			return (0);
		//printf("%s\n\n", str);
		minishell->pretokens = pretokenization(minishell->cmd_line);
		//display_pretokens(pretokens);
		//printf("VALID SYNTAX %s\n\n", check_syntax(pretokens) ? "yes" : "no");
		expand_pretokens(minishell->pretokens);
		//display_pretokens(pretokens);
		minishell->tokens = tokenization(minishell->pretokens);
    	if (!minishell->tokens)
		{
			printf("OLALA\n");
			continue ;
		}
		// display_tokens(minishell->tokens);
		minishell->ast = parser(minishell->tokens);
		init_data(&data, env);
		exec(minishell->ast, &data);
		// if (minishell->ast->type == T_CMD)
		// 	g_status = wait_commands(&data);
		// display_ast(minishell->ast);
		clear_ast(&(minishell->ast));
		printf("g_status = %d\n", g_status);
	}
	return(0);
}
