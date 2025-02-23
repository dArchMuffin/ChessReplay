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
	bool	nl;

	nl = false;
	game = NULL;
	i = 0;
	sep = 0;
	if (game_number != 0)
	{
		while (1)
		{
			nb = read(fd, buf, BUF_SIZE);
			if (nb == 0)
				printf("read() reached end of file\n"); break;
			buf[nb] = '\0';
			i = 0;
			while (buf[i] && sep / 2 != game_number)
			{
				if (buf[i] != '\n')
					nl = false;
				else if (buf[i] == '\n')
				{
					if (nl == true)
					{
						nl = false;
						sep++;
					}
					else
						nl = true;
				}
				i++;
				if (sep / 2 == game_number)
					break ;
			}
			if (sep / 2 == game_number)
			{
				game = ft_substr(buf, i, BUF_SIZE - i);
				break ;
			}
		}
	}
	sep = 0;
	nl = false;
	while (sep < 2)
	{
		nb = read(fd, buf, BUF_SIZE);
		buf[nb] = '\0';
		game = ft_strjoin(game, buf);
		i = 0;
		while (buf[i])
		{
			if (buf[i] != '\n')
				nl = false;
			else if (buf[i] == '\n')
			{
				if (nl == true)
				{
					nl = false;
					sep++;
				}
				else
					nl = true;
			}
			i++;
			if (sep == 2)
				break ;
		}
	}
	return (game);
}

int	header_count(char *game)
{
	int	nb;
	int	i;

	i = 1;
	nb = 0;
	while (game[i])
	{
		if (game[i] == '\n' && game[i - 1] != '\n')
			nb++;
		else if (game[i] == '\n' && game[i - 1] == '\n')
			break ;
		i++;
	}
	return (nb);
}

void	split_headers(char *game, game_info *game_info)
{
	int	i;
	int	j;
	int	start;

	game_info->headers = malloc(sizeof(char *) * header_count(game));
	game_info->nb_headers = header_count(game);
	i = 0;
	j = 0;
	start = -1;
	while (game[i] && j < game_info->nb_headers)
	{
		if (game[i] == '[')
			start = i;
		if (game[i] == '\n' && game[i - 1] != '\n')
		{
			game_info->headers[j] = ft_substr(game, start, i - start);
			j++;
		}
		if (game[i] == '\n' && game[i - 1] == '\n')
			break ;
		i++;
	}
}

int	get_nb_moves(char *game, int len)
{
	int	nb_moves;

	nb_moves = 0;
	while ((len > 0) && (game[len] != ' ' || game[len - 1] != '.'))
		len--;
	while (ft_isdigit(game[len]) == 0 && len > 0)
		len--;
	while (ft_isdigit(game[len]) == 1 && len > 0)
		len--;
	nb_moves = game[len + 1] - '0';
	len++;
	while (game[len + 1] && ft_isdigit(game[len + 1]) == 1 && len > 0)
	{
		nb_moves = nb_moves * 10 + game[len + 1] - '0';
		len++;
	}
	return (nb_moves);
}

void	list_move(char *game, int nb_moves, game_info *infos, move *moves)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < nb_moves * 2)
	{
		while (game[i] && ft_isalpha(game[i]) == 0 && game[i] != 'O')
		{
			i++;
			if ((game[i] == '1' || game[i] == '0') && (game[i + 1] == '/'
					|| game[i + 1] == '-'))
				break ;
		}
		moves[j] = parse_moves(game, i);
		j++;
		while (game[i] && game[i] != ' ')
			i++;
		i++;
		if (game[i] == '{')
		{
			while (game[i] && game[i] != '}')
				i++;
			i += 2;
			while (game[i] && game[i] != ' ')
				i++;
		}
	}
	infos->moves = malloc(sizeof(move) * nb_moves * 2);
	i = 0;
	while (i < nb_moves * 2)
	{
		infos->moves[i] = moves[i];
		i++;
	}
}

int	split_moves(char *game, game_info *game_info, size_t len)
{
	int		nb_moves;
	move	*moves;
	int		i;
	int		j;

	nb_moves = get_nb_moves(game, len);
	game_info->nb_moves = nb_moves * 2;
	moves = malloc(sizeof(move) * nb_moves * 2 + 1);
	list_move(game, nb_moves, game_info, moves);
	if (game_info->headers[game_info->nb_headers - 1][14] == 'T')
		game_info->moves[i - 1].is_time_out = true;
	free(moves);
	return (0);
}

	// split moves debug
	// i = 0;
	// while (i < nb_moves * 2)
	// {
	// 	if ((i == nb_moves - 1))
	// 	{
	// 	printf("\nmoves[%d]\n", i);
	// 	printf("type = %d\n", game_info->moves[i].type);
	// 	printf("pgn = %s\n", game_info->moves[i].pgn);
	// 	printf("eval : %s\n", game_info->moves[i].eval);
	// 	printf("comment : %s\n", game_info->moves[i].comment);
	// 	printf("dest : %s\n", game_info->moves[i].destination);
	// 	printf("col_hint : %c\n", game_info->moves[i].col_hint);
	// 	printf("row_hint : %c\n", game_info->moves[i].row_hint);
	// 	printf("is_check : %d\n", game_info->moves[i].is_check);
	// 	printf("is_mate : %d\n", game_info->moves[i].is_mate);
	// 	printf("is_draw : %d\n", game_info->moves[i].is_draw);
	// 	printf("is resgin : %d\n", game_info->moves[i].is_resign);
	// 	printf("time out = %d\n", game_info->moves[i].is_time_out);
	// 	printf("is_promotion : %d\n", game_info->moves[i].is_promotion);
	// 	printf("promoted : %d\n", game_info->moves[i].promoted);
	// 	}
	// 	i++;
	// }

void	split_game_infos(char *game, game_info *game_info, size_t len)
{
	int		i;
	int		start;
	char	*moves;

	split_headers(game, game_info);
	i = 1;
	while (game[i] && !(game[i] == '\n' && game[i - 1] == '\n'))
		i++;
	i++;
	start = i;
	while (game[i] && game[i] != '\n')
		i++;
	moves = ft_substr(game, start, i - start);
	split_moves(moves, game_info, ft_strlen(moves));
	free(moves);
}

void	free_game_info(game_info *game_info)
{
	int	i;

	i = 0;
	while (i < game_info->nb_moves)
	{
		if (game_info->moves[i].eval)
		{
			free(game_info->moves[i].eval);
			game_info->moves[i].eval = NULL;
		}
		free(game_info->moves[i].pgn);
		game_info->moves[i].pgn = NULL;
		i++;
	}
	i = 0;
	while (i < game_info->nb_headers)
	{
		free(game_info->headers[i]);
		i++;
	}
	free(game_info->headers);
	free(game_info->moves);
}

int	read_game(int game_number, game_info *game_info)
{
	int fd;
	char *game;
	int nl;

	fd = open("gametest9.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error while opening a file\n");
		return (-1);
	}
	printf("searching and parsing game ...\nmMl");
	game = get_game(fd, game_number);
	split_game_infos(game, game_info, ft_strlen(game));
	free(game);
	if (close(fd) < 0)
	{
		printf("Error while closing a file\n");
	}
	return (0);
}
