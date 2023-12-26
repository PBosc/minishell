/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:19:13 by ybelatar          #+#    #+#             */
/*   Updated: 2023/12/26 20:53:51 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int check_quotes(char *str)
{
    int i;
    char c;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            c = str[i];
            while (str[++i] && str[i] != c)
                i++;
            if (!str[i])
                return (0); 
            i++;
        }
        else
            i++;
    }
    return (1);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s2[i] && (s1[i] == s2[i]))
        i++;
    return (s1[i] - s2[i]);
}

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*res;

	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static int	is_in_charset(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		start;
	int		end;
	char	*trimmed;

	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] && is_in_charset(set, s1[start]))
		start++;
	while (end > start && is_in_charset(set, s1[end - 1]))
		end--;
	trimmed = malloc(sizeof(char) * (end - start + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start < end)
		trimmed[i++] = s1[start++];
	trimmed[i] = 0;
	return (trimmed);
}

size_t	ft_strlcpy(char *dst,char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

static char	*empty(void)
{
	char	*err;

	err = malloc(1);
	if (!err)
		return (NULL);
	err[0] = 0;
	return (err);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > (unsigned int)length)
		return (empty());
	if (len > length - start)
		len = length - start;
	res = (char *)malloc((len + 1) * sizeof(*s));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > (unsigned int)length)
		return (empty());
	if (len > length - start)
		len = length - start;
	res = (char *)malloc((len + 1) * sizeof(*s));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
    free(s);
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*res;

	if (!s1)
		return (NULL);
	i = 0;
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		res[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	res[i] = 0;
    //free(s1);
    //free(s2);
	return (res);
}


char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	char	*res;

	if (!s1)
		return (NULL);
	i = 0;
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		res[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	res[i] = 0;
    free(s1);
    //free(s2);
	return (res);
}

char *check_env(char *exp, char *env)
{
    int i;
    int len;
    char *value;
    
    i = 0;
    len = ft_strlen(exp);
    if (exp[i] == '\'')
        return (NULL);
    if (exp[i] == '"')
        exp++;
    while (i < len)
    {
        if (exp[i] != env[i] || env[i] == '=')
            return (NULL);
        i++;
    }
    if (env[i] != '=')
        return (NULL);
    return (ft_substr(env, i + 1, ft_strlen(env) - (i + 1)));
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return ((char *)(s + i + 1));
		}
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}

int     ft_strchri(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return (i);
		}
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

char *expand_env(char *str)
{
    int i;
    char *name;
    char *env_value;

    i = 0;
    name = ft_strchr(str, '$');
    if (!name)
        return (str);
    env_value = getenv(name);
    if (!env_value)
        return (ft_substr_free(str, 0, ft_strchri(str, '$')));
    return (ft_strjoin(ft_substr_free(str, 0, ft_strchri(str, '$')), env_value));
}


int isMatch(char *s, char *p)
{
	int i;
    int sIdx = 0;
	int pIdx = 0;
	int lastWildcardIdx = -1;
	int sBacktrackIdx = -1;
	int nextToWildcardIdx = -1;
    while (sIdx < ft_strlen(s)) {
        if (pIdx < ft_strlen(p) && (p[pIdx] == '?' || p[pIdx] == s[sIdx]))
		{ 
            ++sIdx;
            ++pIdx;
        }
		else if (pIdx < ft_strlen(p) && p[pIdx] == '*')
		{
            lastWildcardIdx = pIdx;
            nextToWildcardIdx = ++pIdx;
            sBacktrackIdx = sIdx;
        }
		else if (lastWildcardIdx == -1)
            return (0);
        else
		{
            pIdx = nextToWildcardIdx;
            sIdx = ++sBacktrackIdx;
        }
    }
	i = pIdx;
	while (i < ft_strlen(p))
	{
        if(p[i] != '*')
			return (0);
		i++;
    }
    return (1);
}

char *expand_wildcard(char *str)
{
	int i;
	char *expanded;
	DIR *dir;
    struct dirent *entry;

	if (!ft_strchr(str, '*'))
		return (str);
	dir = opendir(".");
    if (!dir)
    {
        perror("opendir");
        return (NULL);
    }
	entry = readdir(dir);
	expanded = ft_strdup("");
    while (entry)
    {
		if (isMatch(entry->d_name, str))
		{
			expanded = ft_strjoin_free(expanded, entry->d_name);
			expanded = ft_strjoin_free(expanded, " ");
		}
		entry = readdir(dir);
	}
    closedir(dir);
	free(str);
	return (expanded);
}