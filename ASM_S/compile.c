#include "asm.h"
#include <errno.h>

/*
**	Read complete file at once by using lseek and putting it in buffer.
*/

char			**ft_read_file(char *filename)
{
	int			fd;
	char		*buff;
	char		*tmp;
	size_t		size;
	char		**champion;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error(strerror(errno));
	size = lseek(fd, 0, SEEK_END);	/* Set read pointer to the end of the file so return value is amount of bytes we need to read for the whole file*/
	if ((size < 1) || !(buff = ft_memalloc(size + 1)))
		ft_error("NO VALID FILE");
	lseek(fd, 0, SEEK_SET);	/* Set read pointer to beggining of the file */
	read(fd, buff, size); /* read whole file at once */
	close(fd);
	champion = ft_strsplit(buff, '\n');
	fd = 0;
	while (champion[fd])
	{
		tmp = champion[fd];
		champion[fd] = strtrim(champion[fd]);
		free(tmp);
		fd++;
	}
	ft_strdel(&buff);
	return (champion);
}