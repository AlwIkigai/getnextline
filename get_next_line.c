/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:59:53 by asyed             #+#    #+#             */
/*   Updated: 2024/03/20 14:45:07 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_read(int fd, char *warehouse)
{
	int			bytesread;
	char		*lorry;
	char		*temp;

	lorry = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (lorry == NULL)
		return (NULL);
	bytesread = 1;
	while (bytesread > 0 && ft_strchr(lorry, '\n') == NULL)
	{
		bytesread = read(fd, lorry, BUFFER_SIZE);
		if (bytesread < 0)
		{
			free (lorry);
			free (warehouse);
			return (NULL);
		}
		lorry[bytesread] = '\0';
		temp = ft_strjoin(warehouse, lorry);
		free (warehouse);
		warehouse = ft_strdup(temp);
		free (temp);
	}
	free (lorry);
	return (warehouse);
}

char	*ft_line(char *warehouse)
{
	char	*newline_loc;
	int		line_len;
	char	*line;

	newline_loc = ft_strchr(warehouse, '\n');
	if (newline_loc == NULL)
	{
		line = ft_strdup(warehouse);
		return (line);
	}
	else
	{
		line_len = newline_loc - warehouse + 1;
		line = (char *)ft_calloc(line_len + 1, sizeof(char));
		if (line == NULL)
			return (NULL);
		ft_strlcpy(line, warehouse, line_len + 1);
	}
	return (line);
}

char	*ft_next(char *warehouse )
{
	char		*newline_loc;
	char		*next_line;

	newline_loc = ft_strchr(warehouse, '\n');
	next_line = ft_strdup(newline_loc + 1);
	free (warehouse);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*warehouse = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (warehouse == NULL)
		warehouse = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	warehouse = ft_read(fd, warehouse);
	if (warehouse == NULL || warehouse[0] == '\0')
	{
		free (warehouse);
		warehouse = NULL;
		return (NULL);
	}
	line = ft_line(warehouse);
	if (ft_strchr(warehouse, '\n') == NULL)
	{
		free (warehouse);
		warehouse = NULL;
		return (line);
	}
	warehouse = ft_next(warehouse);
	return (line);
}
