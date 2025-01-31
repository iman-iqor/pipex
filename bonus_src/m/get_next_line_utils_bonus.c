/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:55:53 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/31 21:12:19 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_sstrlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_sstrdup(char *s)
{
	int		len;
	int		i;
	char	*s2;

	len = ft_sstrlen(s);
	s2 = malloc(len + 1);
	i = 0;
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

char	*ft_sstrjoin(char *save, char *buff)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	if (!save && !buff)
		return (NULL);
	if (!save && buff)
		return (ft_sstrdup(buff));
	if (save && !buff)
		return (ft_sstrdup(save));
	len = ft_sstrlen(save) + ft_sstrlen(buff);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (save[++i] && i < ft_sstrlen(save))
		str[i] = save[i];
	j = 0;
	while (buff[j] && j < ft_sstrlen(buff))
		str[i++] = buff[j++];
	str[i] = 0;
	free(save);
	return (str);
}

char	*ft_sstrchr(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}
