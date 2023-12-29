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

char	*ft_read(int fd)
{
	static char	*store = NULL;
	int			bytesread;
	char		*buffalo;
	char		*temp;

	buffalo = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffalo == NULL)
		return (NULL);
	if (store == NULL)
		store = ft_strdup("");
	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffalo, BUFFER_SIZE);
		buffalo[bytesread] = '\0';
		temp = ft_strjoin(store, buffalo);
		store = temp;
		if (ft_strchr(buffalo, '\n'))
			break ;
	}
	free(buffalo);
	if (bytesread < 0)
		return (NULL);
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
		if (temp == NULL) // try a different condition
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
		return (NULL);
	remainder = ft_next(buffer);
	if (remainder == NULL)
		return (NULL);
	free (buffer);
	buffer = ft_strdup(remainder); // find way to free buffer
	return (line);
}
/*
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("tim.txt", O_RDONLY);
	i = 0;
	while (i < 3)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free (line);
		i++;
	}
}


#include <stdio.h>

int main(void)
{
	int	 fd;
	char	*line;

	fd = open("tim.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
		{
			break ;
		}
		//printf("%s", line);
		write(1, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	return (0);
}
*/