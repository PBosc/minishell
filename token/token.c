/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:06:30 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/26 20:52:40 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int is_operator(char *str, t_token **new)
{
    if (!ft_strcmp(str, "&&"))
    {
        (*new)->ope_type = AND_OR;
        return (1);
    }
    else if (!ft_strcmp(str, "||"))
    {
        (*new)->ope_type = AND_OR;
        return (1);
    }
    else if (!ft_strcmp(str, "|"))
    {
        (*new)->ope_type = PIPE;
        return (1);
    }
    else if (!ft_strcmp(str, "<"))
    {
        (*new)->ope_type = REDIRECT_IN;
        return (1);
    }
    else if (!ft_strcmp(str, ">"))
    {
        (*new)->ope_type = REDIRECT_OUT;
        return (1);
    }
    else if (!ft_strcmp(str, ">>"))
    {
        (*new)->ope_type = REDIRECT_APPEND;
        return (1);
    }
    return (0);
}

t_token *new_token(char *str, t_token *last)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    if (!last || last->type == OPERATOR)
    {
        new->type = OPERAND;
        new->ope_type = NOTHING;
    }
    else if (is_operator(str, &new))
        new->type = OPERATOR;
    else if (last->type == OPERAND)
    {
        new->type = ARGUMENT;
        new->ope_type = NOTHING;
    }
    else
    {
        new->type = ARGUMENT;
        new->ope_type = NOTHING;
    }
    new->content = str;
    new->next_token = NULL;
    return (new);
}

t_token *last_token(t_token *token)
{
    if (!token)
        return (NULL);
    while (token->next_token)
        token = token->next_token;
    return (token);
}

void    add_token(t_token **token, char *str)
{
    t_token *new;
    t_token *last;

    last = last_token(*token);
    new = new_token(str, last);
    if (!new)
        return ;
    if (!(*token))
        *token = new;
    else
    {
        last->next_token = new;
        new->prev_token = last;
    }
}

t_token *tokenizer(char *input, char **env)
{
    char **splitted;
    int i;
    static t_token *token = NULL;

    if (!input)
        return (NULL);
    if (!check_quotes(input))
        return (NULL);
    splitted = ft_split(input, ' ');
    if (!splitted)
        return (NULL);
    //expand_env(&splitted, env);
    i = 0;
    while (splitted[i])
    {
        add_token(&token , splitted[i]);
        i++;
    }
    return (token);
}


void    display_tokens(t_token * token)
{
    while (token)
    {
        int a = token->type;
        int b = token->ope_type;
        printf("TOKEN %s OF TYPE %d AND OP_TYPE %d\n\n", token->content, a, b);
        token = token->next_token;
    }
}

int main (int ac, char **av, char **env)
{
    
    display_tokens(tokenizer(av[1], env));

    //printf("test path %s\n",getenv("PAT,P"));
    // int i = 0;
    // while (env[i])
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }
    // dir = opendir(".");
    // if (dir == NULL)
    // {
    //     perror("opendir");
    //     return (1);
    // }
    // while ((entry = readdir(dir)))
    //     printf("%s\n", entry->d_name);
    // closedir(dir);
    return (0);
}


// int main() {
//     DIR *dir;
//     struct dirent *entry;


//     dir = opendir(".");
//     if (dir == NULL)
//     {
//         perror("opendir");
//         return (1);
//     }
//     while ((entry = readdir(dir)))
//         printf("%s\n", entry->d_name);
//     closedir(dir);
//     return (0);
// }