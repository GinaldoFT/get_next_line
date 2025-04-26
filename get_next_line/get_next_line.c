/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:35:02 by ginfranc          #+#    #+#             */
/*   Updated: 2025/04/26 09:32:46 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_ptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*extract_line(char **backup)
{
	char	*line;
	char	*next;
	int		i;

	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if ((*backup)[i] == '\n')
		i++;
	line = ft_substr(*backup, 0, i);
	if (!line)
	{
		free_ptr(backup);
		return (NULL);
	}
	next = ft_strdup(*backup + i);
	free_ptr(backup);
	if (!next || !*line)
	{
		free_ptr(&line);
		free_ptr(&next);
		return (NULL);
	}
	*backup = next;
	return (line);
}

static int	read_into_backup(int fd, char **buffer, char **backup)
{
	char	*tmp;
	int		bytes;

	bytes = 1;
	while (!ft_strchr(*backup, '\n') && bytes > 0)
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (-1);
		(*buffer)[bytes] = '\0';
		tmp = *backup;
		*backup = ft_strjoin(tmp, *buffer);
		free_ptr(&tmp);
		if (!*backup)
			return (-1);
	}
	return (0);
}

static int	test(int fd, char **backup, char **buffer)
{
	int	i;

	i = 0;
	if (!*backup)
		*backup = ft_strdup("");
	if (!*backup || read_into_backup(fd, &*buffer, &*backup) == -1)
	{
		free_ptr(&*buffer);
		free_ptr(&*backup);
		i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer || read(fd, buffer, 0) < 0)
	{
		free_ptr(&buffer);
		free_ptr(&backup);
		return (NULL);
	}
	if (test(fd, &backup, &buffer) != 0)
		return (NULL);
	free_ptr(&buffer);
	if (!*backup)
	{
		free_ptr(&backup);
		return (NULL);
	}
	return (extract_line(&backup));
}

/*
#include <stdio.h>

int	main(int ac, char *av[])
{
	int	fd;
	char	*text;
	int	n;

	if (ac != 2)
		return (1);
	n = 1;
	fd = (int)open(av[1], O_RDONLY);
	while(1)
	{
		text = get_next_line(fd);
		if (!text)
			return (0);
		printf("%s", text);
		free(text);
	}
	return (0);
}
*/
