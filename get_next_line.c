/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:46:31 by asyed             #+#    #+#             */
/*   Updated: 2023/12/15 15:55:44 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

#include "get_next_line.h"

<<<<<<< HEAD
char	*ft_read(int fd)
{
	int		bytesread;
	char	*buffer;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread <= 0)
	{
		free (buffer);
		return (NULL);
	}
	buffer[bytesread] = '\0';
	return (buffer);
}

char	*get_first_line(char *content)
{
	char	*newline_loc;
	size_t	line_len;
	char	*line;

	newline_loc = ft_strchr(content, '\n');
	if (newline_loc == NULL)
		return (ft_strdup(content));
	line_len = newline_loc - content;
	line = (char *)ft_calloc(line_len + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, content, line_len + 1);
	return (line);
}

char	*ft_next(char *content)
{
	static char	*next_line = NULL;
	char		*temp;
	char		*newline_loc;

	newline_loc = ft_strchr(content, '\n');
	if (newline_loc == NULL)
		next_line = ft_strdup("");
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
	line = get_first_line(buffer);
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
	return (line);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tim.txt", O_RDONLY);
	if (fd == -1)
=======
char    *ft_read(int fd)
{
    static char	*store = NULL;
    int     bytesread;
    char    *buffer;
    char	*temp;

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
    	//free(store); // problem
    	store = temp;

    	if(ft_strchr(buffer, '\n'))
    	{
    		break;
    	}
    }
    free(buffer);
    if (bytesread <= 0)
    {
        return (NULL);
    }
    return (store);
}

char    *get_first_line(char *content)
{
    char    *newline_loc;
    int  line_len;
    char    *line;

    newline_loc = ft_strchr(content, '\n');
    if (newline_loc == NULL)
        return (ft_strdup(content));
    line_len = newline_loc - content;
    line = (char *)ft_calloc(line_len + 1, sizeof(char));
    if (line == NULL)
        return (NULL);
    ft_strlcpy(line, content, line_len + 1);
    return (line);
}

char    *ft_next(char *content)
{
    static char *next_line = NULL;
    char        *temp;
    char        *newline_loc;

    newline_loc = ft_strchr(content, '\n');
    if (newline_loc == NULL)
        next_line = ft_strdup(content); // error is here
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

char    *get_next_line(int fd)
{
    static char *remainder = NULL;
    static char        *buffer;
    char        *line;

    buffer = ft_read(fd);
    if (buffer == NULL)
        return (NULL);
    line = get_first_line(buffer);
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
    buffer = ft_strdup(remainder); // clean up
    return (line);
}

#include <stdio.h>
/*
int	main(void)
{
	int	fd;
	int	i;
	char	*a;

	fd = open("tim.txt", O_RDONLY);
	i = 0;
	while (i < 2)
>>>>>>> 0b3dca3b8b7e1091b5333ccbfa04403ef38ec572
	{
		a = get_next_line(fd);
		printf("%s", a);
		free (a);
		i++;
	}
<<<<<<< HEAD
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free (line);
	close(fd);
	return (0);
}
=======
	return (0);
}
*/

int main(void)
{
    int     fd;
    char    *line;

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
>>>>>>> 0b3dca3b8b7e1091b5333ccbfa04403ef38ec572
