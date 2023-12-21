/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:46:56 by asyed             #+#    #+#             */
/*   Updated: 2023/12/14 19:22:19 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//ft_calloc

void	ft_bzero(void *ptrmemadd, size_t n)
{
	unsigned char	*p;

	p =(unsigned char *)ptrmemadd;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}
char	*ft_calloc(size_t element, size_t size) // char *fx due to calloc type
{
	void	*p;

	p = malloc(element * size);
	if (p != NULL)
		ft_bzero(p, element * size);
	return (p); // return something and not void
}

//ft_strlen

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

//ft_strchr -> return everything after \n

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char) c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

//ft_strlcpy

//ft_strdup
char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dup)
		return (0);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char		*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d > s && d < s + n)
		return (NULL);
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

//ft_strjoin
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if(s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len1 + len2 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	return (result);
}

