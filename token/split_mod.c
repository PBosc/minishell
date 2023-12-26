/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:55:09 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/26 20:36:51 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"


static void skip_to_next_quote(char const *str, int *i, char quote)
{
    while (str[*i] != quote)
        *i = *i + 1;
    *i = *i + 1;
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
		}
        else if (str[i] == '\'' || str[i] == '"')
        {
            count++;
            i++;
            skip_to_next_quote(str, &i, str[i - 1]);
        }
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*get_next_word(char const *str, int *ptr, char c)
{
	int		i;
	int		len_word;
	char	*word;

	i = 0;
	len_word = 0;
	while (str[*ptr] && str[*ptr] == c)
		*ptr = *ptr + 1;
	if (!str[*ptr])
		return (NULL);
    if (str[*ptr] == '\'' || str[*ptr] == '"')
    {
        len_word++;
	    while (str[*ptr + len_word] && str[*ptr + len_word] != str[*ptr])
		    len_word++;
        len_word++;
    }
    else
    {
	    while (str[*ptr + len_word] && str[*ptr + len_word] != c)
		    len_word++;
    }
	word = malloc((len_word + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[*ptr];
		i++;
		*ptr = *ptr + 1;
	}
	word[i] = 0;
	word = expand_env(word);
	word = expand_wildcard(word);
	return (word);
}

void    free_rest(char ***words, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        free(words[j]);
        j++;
    }
    free(words);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**words;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	count = count_words(s, c);
	words = malloc((count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (i < count)
	{
		words[i] = get_next_word(s, &j, c);
		if (!words[i])
			return (free_rest(&words, i), NULL);
		i++;
	}
	words[i] = 0;
	return (words);
}
