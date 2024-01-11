/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:45:33 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/10 22:46:55 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H

# define FT_DPRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

void	ft_match(char c, va_list *parameters, int *length, int fd);
int		ft_dprintf(int fd, const char *str, ...);
void	ft_putstrbis(char *str, int *length, int fd);
void	ft_putptrhexabis(uintptr_t ptr, int *length, int fd);
void	ft_putnbrbasebis(uintptr_t n, int mix, int *length, int fd);
void	ft_putnbrdecabis(int n, int *length, int fd);
void	ft_putcharbis(char c, int *length, int fd);

#endif