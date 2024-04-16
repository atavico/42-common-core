/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:32:49 by atarsi            #+#    #+#             */
/*   Updated: 2022/03/18 19:29:27 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define BUFFER_SIZE 1

size_t	ft_strlen2(const char *s);
int		ft_strchr2(const char *s, int c);
char	*ft_strjoin2(char const *str, char const *buffer);
char	*get_next_line(int fd);
char	*ft_save(char *str);
void	ft_strcpy2(char *str, char *ret, int i);

#endif