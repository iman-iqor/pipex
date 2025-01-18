/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:00:58 by imiqor            #+#    #+#             */
/*   Updated: 2024/11/20 17:07:27 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	check_and_fetch(char format, int *len, va_list params);
void	ft_hexa_upper(unsigned int n, int *len);
void	ft_hexa_lower(unsigned int n, int *len);
void	ft_pointer(unsigned long nb, int *len);
void	ft_pointerr(unsigned long nb, int *len);
void	ft_put_unsigned_nbr(unsigned int n, int *len);
void	ft_str(char *s, int *len);
void	ft_putnumber(int n, int *len);
void	ft_putchar(char c, int *len);
#endif