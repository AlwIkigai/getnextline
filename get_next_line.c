/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:46:31 by asyed             #+#    #+#             */
/*   Updated: 2023/11/09 16:46:33 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

//get_first_line(char *firstline)
//get_other_lines
//read

char	*get_next_line(int fd)
{
	int	bytesreading;
	char	*box;
	char	*lorry;
	char	*temp;
	char	*newlineloc;
	size_t	line_len;
	char	*firstline;
	//char	*secondline;
	static char	*last_newline = NULL;

	box = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (box == NULL)
		return (NULL);
	lorry = ft_strdup("");

	while ((bytesreading = read(fd, box, BUFFER_SIZE)) > 0)
	{
		// concatenate box into lorry
		temp = ft_strjoin(lorry, box);
		free(lorry);
		lorry = temp;
		// find '\n' loc
		newlineloc = ft_strchr(lorry, '\n');
		if (newlineloc != NULL)
		{
			// find firstline
			line_len = newlineloc - lorry;
			firstline = (char *)ft_calloc(line_len + 1, sizeof(char));
			if (firstline == NULL)
			{
				free (lorry);
				return (NULL);
			}
			ft_strlcpy(firstline, lorry, line_len + 1);
			
			// update newline loc using static char
			last_newline = ft_strdup(newlineloc + 1);
			free(lorry);
			return (firstline);

		}
		//concatenate box to lorry
		//check for newline in lorry
		//if newline found, split lorry firstline and last newline
		//return firstline
	}

	if (bytesreading == 0 && lorry[0] != '\0')
	{
		return(lorry);
	}
	free(lorry);

	if (fd < 0 || bytesreading < 0)
	{
		free (lorry);
		return (NULL);
	}
	return (last_newline);
}

int	main(void)
{
	int fd;
	char *line;

	// open .txt, O_RDONLY

	fd = open("tim.txt", O_RDONLY);

	if (fd == -1) // A file descriptor is an unsigned integer used by a process to identify an open file
	{
		perror("error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}	
	// free (line) -- this is where we free line for mem alloc
	close(fd);
	return (0);
}
