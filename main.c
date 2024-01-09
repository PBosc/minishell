/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:54:26 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/09 06:42:35 by ybelatar         ###   ########.fr       */
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

t_env *new_env(char *key, char *value, int i)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	if (i)
		new->value = ft_strdup(getenv(key));
	else
		new->value = value;
	new->next_env = NULL;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env *last;
	
	if (!new || !env)
		return ;
	if (!*env)
		*env = new;
	else
	{
		last = *env;
		while (last->next_env)
			last = last->next_env;
		last->next_env = new;
	}
}

t_env *copy_env(char **env)
{
	int i;
	t_env *cpy;

	if (!env)
		return (NULL);
	cpy = NULL;
	i = 0;
	while (env[i])
	{
		env_add_back(&cpy, new_env(ft_substr(env[i], 0, ft_strchri(env[i], '=')), NULL, 1));
		i++;
	}
	return (cpy);
}



int	main(int ac, char **av, char **env)
{
	t_minishell *minishell;
	t_exec		data;

	(void)ac;
	(void)av;
	
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (1);
	minishell->env = copy_env(env);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		minishell->cmd_line = readline("minishell$ ");
		if (!minishell->cmd_line)
			return (ft_dprintf(2, "exit\n"), 0);
		if (!minishell->cmd_line || !*minishell->cmd_line)
			continue ;
		if (*minishell->cmd_line)
			add_history(minishell->cmd_line);
		// if (!ft_strcmp(minishell->cmd_line, "exit"))
		// 	return (0);
		minishell->pretokens = pretokenization(minishell->cmd_line);
		//display_pretokens(minishell->pretokens);
		//display_env(minishell)
		expand_pretokens(minishell->pretokens, minishell);
		//display_pretokens(minishell->pretokens);
		minishell->tokens = tokenization(minishell->pretokens);
		if (!minishell->tokens)
		{
			printf("Aucun token renvoye\n");
			continue ;
		}
		minishell->ast = parser(minishell->tokens);
		//display_ast(minishell->ast);
		// clear_ast(&(minishell->ast));
		// exit(g_status);
		// printf("%s\n\n", minishell->cmd_line);
		//display_pretokens(pretokens);
		//printf("VALID SYNTAX %s\n\n", check_syntax(pretokens) ? "yes" : "no");
    	// if (!minishell->tokens)
		// {
		// 	printf("OLALA\n");
		// 	continue ;
		// }
		// display_tokens(minishell->tokens);
		init_data(&data, minishell->env);
		exec(minishell->ast, &data, minishell);
		clear_ast(&(minishell->ast));
		//printf("g_status = %d\n", g_status);
		// exit(g_status);
	}
	return(0);
}
