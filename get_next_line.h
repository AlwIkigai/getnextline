/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:47:08 by asyed             #+#    #+#             */
/*   Updated: 2023/12/14 19:19:49 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
void	ft_bzero(void *ptrmemadd, size_t n);
char	*ft_calloc(size_t element, size_t size);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dest, void *src, size_t n);

#endif