/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:47:22 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/08 22:22:52 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static char	*get_first_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || str[0] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i])
		line[i] = str[i];
	line[i + (str[i] == '\n')] = 0;
	return (line);
}

static char	*get_end(char *str)
{
	int		i;
	char	*end;
	char	*tmp;

	i = 0;
	tmp = ft_strchr(str, '\n');
	if (!tmp)
		return (free(str), NULL);
	while (str && str[i] && str[i] != '\n')
		i++;
	end = malloc(ft_strlen(str) - i);
	if (!end)
		return (NULL);
	tmp++;
	i = 0;
	while (tmp && *tmp)
		end[i++] = *tmp++;
	end[i] = 0;
	return (free(str), end);
}

static char	*read_line(char *save, int fd)
{
	char	*buf;
	char	*tmp;
	int		ret;

	ret = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	while (ret > 0 && !ft_strchr(buf, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (free(buf), NULL);
		buf[ret] = 0;
		if (!save)
			save = ft_calloc(1, 1);
		if (!save)
			return (NULL);
		tmp = save;
		save = ft_strjoin(save, buf);
		free(tmp);
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (free(buf), save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd == -42)
		return (free(save), NULL);
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save = read_line(save, fd);
	if (!save)
		return (NULL);
	line = get_first_line(save);
	if (line[ft_strlen(line) - 1] == '\n')
		save = get_end(save);
	return (line);
}
