/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:26:44 by imiqor            #+#    #+#             */
/*   Updated: 2024/11/20 17:06:49 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pointer(unsigned long nb, int *len)
{
	ft_putchar('0', len);
	ft_putchar('x', len);
	ft_pointerr(nb, len);
}

void	ft_hexa_lower(unsigned int n, int *len)
{
	char	*hexa_lower;

	hexa_lower = "0123456789abcdef";
	if (n >= 16)
	{
		ft_hexa_lower(n / 16, len);
	}
	ft_putchar(hexa_lower[n % 16], len);
}

void	ft_hexa_upper(unsigned int n, int *len)
{
	char	*hexa_upper;

	hexa_upper = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_hexa_upper(n / 16, len);
	}
	ft_putchar(hexa_upper[n % 16], len);
}

void	check_and_fetch(char format, int *len, va_list params)
{
	if (format == 'i' || format == 'd')
		ft_putnumber(va_arg(params, int), len);
	else if (format == 's')
		ft_str(va_arg(params, char *), len);
	else if (format == 'c')
		ft_putchar(va_arg(params, int), len);
	else if (format == '%')
		ft_putchar('%', len);
	else if (format == 'u')
		ft_put_unsigned_nbr(va_arg(params, unsigned int), len);
	else if (format == 'p')
		ft_pointer(va_arg(params, unsigned long), len);
	else if (format == 'x')
		ft_hexa_lower(va_arg(params, unsigned int), len);
	else if (format == 'X')
		ft_hexa_upper(va_arg(params, unsigned int), len);
}

int	ft_printf(const char *format, ...)
{
	va_list	params;
	int		len;
	int		i;

	va_start(params, format);
	len = 0;
	i = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			check_and_fetch(format[i], &len, params);
		}
		else
		{
			ft_putchar(format[i], &len);
		}
		i++;
	}
	va_end(params);
	return (len);
}
