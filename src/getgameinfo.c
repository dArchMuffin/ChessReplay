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
	// Looking for a specific game if inputed
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
	// concat headers and moves in 1 char*
	while (sep < 2)
	{
		nb = read(fd, buf, BUF_SIZE);
		// Gerer le cas particulier ou le buf coupe un double \n
		buf[nb] = '\0';
		game = ft_strjoin(game, buf);
		// printf("game = %s\n", game);
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
	// printf("game[%d] = %c\n", i, game[i]);
	// printf("sep = %d\ngame = %s\nbuf = %s\n", sep, game, buf);
	return (game);
}

int	parse_moves(char *game, game_info *game_info, size_t len)
// invalid read size
{
	// move m;
	int nb_moves;
	int i;

	// i = ft_strlen(game);
	// printf("len = %d\n", len);
	nb_moves = 0;
	while (game[i] != '.' && game[i + 1] != ' ')
		i--;
	// printf("game[%d] = %c\n", i, game[i]);
	while (game[i] > '9' && game[i] < '0')
		i--;
	// printf("game[%d] = %c\n", i, game[i]);
	nb_moves = game[i] - '0';
	i--;
	// printf("game[%d] = %c\n", i, game[i]);
	while (game[i] <= '9' && game[i] >= '0')
	{
		// printf("game[%d] = %c\n", i, game[i]);
		nb_moves = nb_moves * 10 + (game[i] - '0');
		i--;
	}
	// printf("nb_moves = %d\n", nb_moves);
}

void	split_game_infos(char *game, game_info *game_info, size_t len)
{
	int		nb_headers;
	char	**headers;
	int		i;
	int		j;
	int		start;
	char	*moves;

	i = 1;
	nb_headers = 0;
	while (game[i])
	{
		if (game[i] == '\n' && game[i - 1] != '\n')
			nb_headers++;
		else if (game[i] == '\n' && game[i - 1] == '\n')
			break ;
		i++;
	}
	game_info->headers = malloc(sizeof(char *) * nb_headers);
	game_info->nb_headers = nb_headers;
	i = 1;
	j = 0;
	start = -1;
	while (game[i] && j < nb_headers)
	{
		if (game[i] == '\n' && game[i - 1] == '\n')
			break ;
		if (game[i] == '[')
			start = i;
		if (game[i] == '\n' && game[i - 1] != '\n')
		{
			game_info->headers[j] = ft_substr(game, start, i - start);
			j++;
		}
		i++;
	}
	start = i + 1;
	i++;
	while (game[i] != '\n')
		i++;
	moves = ft_substr(game, start, i - start);
	printf("len game = %d\n", ft_strlen(game));
	// parse_moves(game, game_info, ft_strlen(game));
	free(moves);
}

void	free_game_info(game_info *game_info)
{
	int	i;

	i = 0;
	while (i < game_info->nb_headers)
	{
		free(game_info->headers[i]);
		i++;
	}
	free(game_info->headers);
}

int	read_game(int game_number, game_info *game_info)
{
	int fd;
	char *game;
	int nl;

	// opening file with game(s)
	fd = open("gametest2.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error while opening a file\n");
		return (-1);
	}
	// getting a char * with headers and moves + filling game_info->headers
	game = get_game(fd, game_number);
	// printf("game = %s\n", game);
	// spliting moves in a tab of structs inside game_info struct
	split_game_infos(game, game_info, ft_strlen(game));
	free(game);
	if (close(fd) < 0)
	{
		printf("Error while closing a file\n");
	}
	return (0);
}