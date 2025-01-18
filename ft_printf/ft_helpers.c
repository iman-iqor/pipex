/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:00:39 by imiqor            #+#    #+#             */
/*   Updated: 2024/11/21 23:32:31 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putnumber(int n, int *len)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchar('-', len);
		nb *= -1;
	}
	if (nb < 10)
		ft_putchar(nb + 48, len);
	else
	{
		ft_putnumber(nb / 10, len);
		ft_putnumber(nb % 10, len);
	}
	(void)len;
}

void	ft_str(char *s, int *len)
{
	int		i;
	char	*null;

	i = 0;
	if (!s)
	{
		null = "(null)";
		while (null[i])
		{
			ft_putchar(null[i++], len);
		}
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i++], len);
	}
}

void	ft_put_unsigned_nbr(unsigned int n, int *len)
{
	if (n < 10)
	{
		ft_putchar(n + 48, len);
	}
	else
	{
		ft_put_unsigned_nbr(n / 10, len);
		ft_put_unsigned_nbr(n % 10, len);
	}
	(void)len;
}

void	ft_pointerr(unsigned long nb, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb >= 16)
		ft_pointerr(nb / 16, len);
	ft_putchar(hexa[nb % 16], len);
}
