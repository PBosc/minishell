/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:54:26 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/02 02:48:54 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	while (token)
	{
		a = token->type;
		printf("TOKEN %s OF TYPE %d\n      |\n", token->content, a);
		token = token->next_token;
	}
}

#define COUNT 10

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
	printf("%d\n", a);
	printutil(root->left_child, space);
}

void	display_ast(t_node_ast *root)
{
	printutil(root, 0);
}

int	main(int ac, char **av)
{
	char		*str;
	t_pretoken	*pretokens;
	t_token		*tokens;
	t_node_ast	*ast;

	(void)ac;
	// (void)av;
	str = av[1];
	pretokens = pretokenization(str);
	// display_pretokens(pretokens);
	printf("VALID SYNTAX %s\n\n", check_syntax(pretokens) ? "yes" : "no");
	expand_pretokens(pretokens);
	// display_pretokens(pretokens);
	tokens = tokenization(pretokens);
	// display_tokens(tokens);
	ast = parser(tokens);
	display_ast(ast);
}
