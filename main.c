/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:48:01 by asyed             #+#    #+#             */
/*   Updated: 2024/02/08 11:48:05 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)

{
	int		fd;
	char	*mainline;

	fd = open("tim.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("error opening file");
		return (1);
	}
	printf("%s\n", "test case, this is for tim.txt; SEE BELOW OUTPUT:");
	while ((mainline = get_next_line(fd)) != NULL)
	{
		printf("%s", mainline);
		free (mainline);
	}
	close(fd);

	fd = open("empty.txt", O_RDONLY);
	printf("%s\n", "test case, this is for empty.txt; SEE BELOW OUTPUT:");
	while ((mainline = get_next_line(fd)) != NULL)
	{
		printf("%s\n", mainline);
		free (mainline);
	}
	close(fd);

	fd = open("0.txt", O_RDONLY);
	printf("%s\n", "test case, this is for 0.txt; SEE BELOW OUTPUT:");
	while ((mainline = get_next_line(fd)) != NULL)
	{
		printf("%s\n", mainline);
		free (mainline);
	}
	close(fd);

	char *t;

	t = NULL;
	printf("%s\n", "test case, this is for NULL; SEE BELOW OUTPUT:");
	printf("%s\n", t);
	return (0);
}
