/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:00:58 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/07 21:27:53 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

int		ft_fprintf(int fd, const char *format, ...);
void	fcheck_and_fetch(int fd, char format, int *len, va_list params);
void	ft_fhexa_upper(int fd, unsigned int n, int *len);
void	ft_fhexa_lower(int fd, unsigned int n, int *len);
void	ft_fpointer(int fd, unsigned long nb, int *len);
void	ft_fpointerr(int fd, unsigned long nb, int *len);
void	ft_fput_unsigned_nbr(int fd, unsigned int n, int *len);
void	ft_fstr(int fd, char *s, int *len);
void	ft_fputnumber(int fd, int n, int *len);
void	ft_fputchar(int fd, char c, int *len);
#endif