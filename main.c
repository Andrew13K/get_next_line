#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int main()
{
	char *line;
	int count = 0;
	int fd = open("text.txt", O_RDWR);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line [%d]: %s\n", count, line);
		free(line);
		++count;
	}
	close(fd);
	return 0;
}