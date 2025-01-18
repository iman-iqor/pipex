/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:26:44 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/12 12:45:38 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fpointer(int fd, unsigned long nb, int *len)
{
	ft_fputchar(fd, '0', len);
	ft_fputchar(fd, 'x', len);
	ft_fpointerr(fd, nb, len);
}

void	ft_fhexa_lower(int fd, unsigned int n, int *len)
{
	char	*hexa_lower;

	hexa_lower = "0123456789abcdef";
	if (n >= 16)
	{
		ft_fhexa_lower(fd, n / 16, len);
	}
	ft_fputchar(fd, hexa_lower[n % 16], len);
}

void	ft_fhexa_upper(int fd, unsigned int n, int *len)
{
	char	*hexa_upper;

	hexa_upper = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_fhexa_upper(fd, n / 16, len);
	}
	ft_fputchar(fd, hexa_upper[n % 16], len);
}

void	fcheck_and_fetch(int fd, char format, int *len, va_list params)
{
	if (format == 'i' || format == 'd')
		ft_fputnumber(fd, va_arg(params, int), len);
	else if (format == 's')
		ft_fstr(fd, va_arg(params, char *), len);
	else if (format == 'c')
		ft_fputchar(fd, va_arg(params, int), len);
	else if (format == '%')
		ft_fputchar(fd, '%', len);
	else if (format == 'u')
		ft_fput_unsigned_nbr(fd, va_arg(params, unsigned int), len);
	else if (format == 'p')
		ft_fpointer(fd, va_arg(params, unsigned long), len);
	else if (format == 'x')
		ft_fhexa_lower(fd, va_arg(params, unsigned int), len);
	else if (format == 'X')
		ft_fhexa_upper(fd, va_arg(params, unsigned int), len);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	params;
	int		len;
	int		i;

	va_start(params, format);
	len = 0;
	i = 0;
	if (write(fd, 0, 0) == -1)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			fcheck_and_fetch(fd, format[i], &len, params);
		}
		else
		{
			ft_fputchar(fd, format[i], &len);
		}
		i++;
	}
	va_end(params);
	return (len);
}
