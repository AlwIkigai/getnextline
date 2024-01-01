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
		if (bytesread == 0)
			break ;
		else if (bytesread < 0)
		{
			free (lorry);
			free (warehouse);
			return (NULL);
			//if (temp != NULL)
			//	free (temp);
			warehouse = NULL;
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
		line = ft_strdup(warehouse);
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

char	*ft_next(char *warehouse)
{
	char		*newline_loc;
	char		*next_line;

	newline_loc = ft_strchr(warehouse, '\n');
	if (newline_loc == NULL)
		next_line = ft_strdup(warehouse);
	else
	// condition to output last line
	{
		next_line = ft_strdup(newline_loc + 1);
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*warehouse = NULL;
	char		*line;
	char		*update_store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (warehouse == NULL)
	{
		warehouse = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		//warehouse[0] = '\0';
	}
	warehouse = ft_read(fd, warehouse);
	{
	if (warehouse == NULL || warehouse[0] == '\0')
		{
		free (warehouse);
		warehouse = NULL;
		return (NULL);
		}
	}
	line = ft_line(warehouse);
	if (line == NULL)
		return (NULL);
	update_store = ft_next(warehouse);
	if (update_store == NULL)
		return (NULL);
	//free (warehouse);
	warehouse = update_store;

	if (ft_strchr(warehouse, '\n') == NULL)
	{
		line = ft_strdup(warehouse);
		free (warehouse);
		warehouse = NULL;
		return (line);
	}

/*	if (warehouse[0] == '\0')
	{
		free (warehouse);
		warehouse = NULL;
	}*/
	return (line);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*mainline;

	fd = open("tim.txt", O_RDONLY);
	i = 0;
	while ((mainline = get_next_line(fd)) != NULL)
	{
		printf("%s", mainline);
		free (mainline);
		i++;
	}
	mainline = get_next_line(fd);
	free (mainline);
}

/*
#include <stdio.h>
int     main(void)
{
        char    *line;
//      int     i = 0;
        int fd = open("tests/only_nl.txt", O_RDONLY);
        
//      while ((line = get_next_line(fd)) != NULL && i < 3)
//      {
//              printf("%s\n", line);
//              free(line);
//              i++;
//      }

        line = get_next_line(fd);
        printf("%s", line);
        free(line);     
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
        line = get_next_line(fd);

        printf("%s", line);
        free(line);
        
        close(fd);
        return (0);
}

#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*mainline;

	fd = open("tim.txt", O_RDONLY);
	i = 0;
	while (i < 1)
	{
		mainline = get_next_line(fd);
		printf("%s", mainline);
		free (mainline);
		i++;
	}
}

*/
