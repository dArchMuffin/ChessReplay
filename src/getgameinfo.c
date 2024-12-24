#ifndef BUF_SIZE
# define BUF_SIZE 50
#endif

#include "header.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_game(int fd, int game_number)
{
	char	buf[BUF_SIZE + 1];
	int		nb;
	int		sep;
	char	*game;
	int		i;

	game = NULL;
	i = 0;
	sep = 0;
	if (game_number != 0)
	{
		while (1)
		{
			nb = read(fd, buf, BUF_SIZE);
			i = 1;
			while (buf[i])
			{
				if (buf[i] == '\n' && buf[i - 1] == '\n')
					sep++;
				if (sep / 2 == game_number)
					break ;
				i++;
			}
		}
	}
	sep = 0;
	while (sep < 2)
	{
		nb = read(fd, buf, BUF_SIZE);
		buf[nb] = '\0';
		game = ft_strjoin(game, buf);
		i = 0;
		while (buf[i])
		{
			if (buf[i] == '\n' && buf[i - 1] == '\n')
				sep++;
			if (sep == 2 || !buf[i])
				break ;
			i++;
		}
	}
	// Boucle infinie + gérer le cas ou le sep est entre deux bufs
	printf("sep = %d\ngame = %s\nbuf = %s\n", sep, game, buf);
}

int	read_game(int game_number, game_info *game_info)
{
	int fd;
	char *game;
	int nl;

	fd = open("gametest2.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error while opening a file\n");
		return (-1);
	}
	// if (game_number > 0)
	// {
	// 	nl = 0;
	// 	while (nl / 2 <= game_number && data != NULL)
	// 	{
	// 		data = get_next_line(fd);
	// 		if (data[0] == '\n')
	// 			nl++;
	// 		free(data);
	// 	}
	// }
	game = get_game(fd, game_number);
	if (close(fd) < 0)
	{
		printf("Error while closing a file\n");
	}
	return (0);
}