/* ************************************************************************** */
/*										  */
/*							  :::	   ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*							  +:+ +:+		  +:+	 */
/*   By: asyed <marvin@42.fr>				+#+  +:+	   +#+		  */
/*						  +#+#+#+#+#+	+#+		  */
/*   Created: 2023/11/09 16:46:31 by asyed		   #+#	#+#		  */
/*   Updated: 2023/12/28 13:59:56 by asyed            ###   ########.fr       */
/*										  */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t element, size_t size) // char *fx due to calloc type
{
	void			*p;
	unsigned char	*pz;
	size_t			b;

	p = malloc(element * size);
	if (p != NULL)
	{
		pz = (unsigned char *)p;
		b = element * size;
		while (b > 0)
		{
			*pz = 0;
			pz++;
			b--;
		}
	}
	return (p);
}

char	*ft_read(int fd)
{
	static char	*store = NULL;
	int			bytesread;
	char		*buffer;
	char		*temp;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	if (store == NULL)
		store = ft_strdup("");
	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		buffer[bytesread] = '\0';
		temp = ft_strjoin(store, buffer);
		store = temp;
		if (ft_strchr(buffer, '\n'))
		{
			break ;
		}
	}
	free(buffer);
	if (bytesread < 0)
	{
		return (NULL);
	}
	return (store);
}

char	*ft_line(char *buffer)
{
	char	*newline_loc;
	int		line_len;
	char	*line;

	newline_loc = ft_strchr(buffer, '\n');
	if (newline_loc == NULL)
		return (ft_strdup(buffer));
	line_len = newline_loc - buffer + 1;
	line = (char *)ft_calloc(line_len + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, buffer, line_len + 1);
	return (line);
}

char	*ft_next(char *buffer)
{
	static char	*next_line = NULL;
	char		*temp;
	char		*newline_loc;

	newline_loc = ft_strchr(buffer, '\n');
	if (newline_loc == NULL)
		next_line = ft_strdup(buffer);
	else
	{
		temp = ft_strdup(newline_loc + 1);
		if (temp == NULL)
			return (NULL);
		free (next_line);
		next_line = temp;
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*buffer;
	char		*line;

	buffer = ft_read(fd);
	if (buffer == NULL)
		return (NULL);
	line = ft_line(buffer);
	if (line == NULL)
	{
		free (buffer);
		return (NULL);
	}
	remainder = ft_next(buffer);
	if (remainder == NULL)
	{
		free (buffer);
		return (NULL);
	}
	free (buffer);
	buffer = ft_strdup(remainder);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	int	fd;
	int	i;
	char	*a;

	fd = open("tim.txt", O_RDONLY);
	i = 0;
	while (i < 6)
	{
		a = get_next_line(fd);
		printf("%s", a);
		free (a);
		i++;
	}
}
/*
int main(void)
{
	int	 fd;
	char	*line;

	fd = open("tim.txt", O_RDONLY);
	if (fd == -1)
	{
	perror("error opening file");
	return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
*/
