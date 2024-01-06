/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:59:08 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/05 17:22:42 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_data(t_exec *data, char **env)
{
	data->env = env;
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->prev_pipe = -1;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->is_pipe = 0;
	data->ret_value = EXIT_SUCCESS;
}
