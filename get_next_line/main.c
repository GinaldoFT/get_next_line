#include "get_next_line.h"
#include <stdio.h>

int	main(int ac, char *av[])
{
	int	fd;
	char	*text;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	while (1)
	{
		text = get_next_line(fd);
		if (!text)
			return (0);
		printf("%s", text);
		free(text);
	}
	close(fd);
	return (0);
}
