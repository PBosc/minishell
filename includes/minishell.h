/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:54:49 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/12 02:01:46 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "exec.h"
# include "parsing.h"
# include "ft_dprintf.h"
# include <sys/types.h>
# include <sys/stat.h>

extern int	g_status;

void	sig_handler(int sig);

#endif