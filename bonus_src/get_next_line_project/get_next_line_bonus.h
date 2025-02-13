/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:56:11 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/31 21:07:14 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13847748
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_sstrjoin(char *save, char *buff);
char	*ft_sstrdup(char *s);
int		ft_sstrlen(char *s);
char	*ft_sstrchr(char *str, int c);
char	*ft_extract_line(char *str);
char	*clean_buffer(char *buff);
char	*read_from_file(char *save, int fd);
char	*get_next_line(int fd);
#endif