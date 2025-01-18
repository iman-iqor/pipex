/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:00:39 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/12 12:47:56 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fputchar(int fd, char c, int *len)
{
	write(fd, &c, 1);
	(*len)++;
}

void	ft_fputnumber(int fd, int n, int *len)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		ft_fputchar(fd, '-', len);
		nb *= -1;
	}
	if (nb < 10)
		ft_fputchar(fd, nb + 48, len);
	else
	{
		ft_fputnumber(fd, nb / 10, len);
		ft_fputnumber(fd, nb % 10, len);
	}
	(void)len;
}

void	ft_fstr(int fd, char *s, int *len)
{
	int		i;
	char	*null;

	i = 0;
	if (!s)
	{
		null = "(null)";
		while (null[i])
		{
			ft_fputchar(fd, null[i++], len);
		}
		return ;
	}
	while (s[i])
	{
		ft_fputchar(fd, s[i++], len);
	}
}

void	ft_fput_unsigned_nbr(int fd, unsigned int n, int *len)
{
	if (n < 10)
	{
		ft_fputchar(fd, n + 48, len);
	}
	else
	{
		ft_fput_unsigned_nbr(fd, n / 10, len);
		ft_fput_unsigned_nbr(fd, n % 10, len);
	}
	(void)len;
}

void	ft_fpointerr(int fd, unsigned long nb, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb >= 16)
		ft_fpointerr(fd, nb / 16, len);
	ft_fputchar(fd, hexa[nb % 16], len);
}
