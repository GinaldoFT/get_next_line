/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:35:02 by ginfranc          #+#    #+#             */
/*   Updated: 2025/04/24 10:36:05 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;
	int		i;

	i = 0;
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
        return (NULL);

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(line);
		return (NULL);
	}

	while (i < bytes_read && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}

	if (buffer[i] == '\n')
		line[i++] = '\n';

	line[i] = '\0';
	return (line);
}

#include <stdio.h>

int	main(int ac, char *av[])
{
	int	fd;
	char	*text;
	int	n;

	if (ac != 2)
		return (1);
	n = 4;
	fd = (int)open(av[1], O_RDONLY);
	while (--n > 0)
	{
		text = get_next_line(fd);
		printf("%s", text);
		free(text);
	}
	return (0);
}

