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

void	split_headers(char *game, game_info *game_info)
{
	int	i;
	int	nb_headers;
	int	j;
	int	start;

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
	i = 0;
	j = 0;
	start = -1;
	while (game[i] && j < nb_headers)
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

move	parse_moves(char *game, int i)
{
	move	m;
	int		start;
	int		j;
	int		len;

	// bricolage a revoir
	// on copie le code pgn dans la structure
	start = i;
	while (game[i] != ' ')
		i++;
	m.pgn = ft_substr(game, start, i - start);
	len = ft_strlen(m.pgn);
	i = start;
	// 1 : cas où on cherche un char dans le move : ADD 1/2 1/2 !
	// O : Castles
	if (game[i] == 'O')
	{
		if (game[i + 3] == '-')
			m.type = LONG_CASTLE;
		else
			m.type = SHORT_CASTLE;
	}
	//+ : check
	i = start;
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == '+')
		{
			m.is_check = true;
			break ;
		}
		i++;
	}
	if (game[i] == ' ')
		m.is_check = false;
	// x : capture
	i = start;
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == 'x')
		{
			m.type = CAPTURE;
			break ;
		}
		i++;
	}
	if (game[i] == ' ')
		m.type = NORMAL;
	//# : checkmate
	i = start;
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == '#')
		{
			m.is_mate = true;
			break ;
		}
		i++;
	}
	if (game[i] == ' ')
		m.is_mate = false;
	//! ? : comments
	i = start;
	j = 0;
	while (i - start < len && game[i] != ' ')
	{
		if (game[i] == '!' || game[i] == '?')
		{
			m.comment[j] = game[i];
			j++;
		}
		i++;
	}
	m.comment[j] = '\0';
	i = start;
	// 2 : which piece is moving ?
	if (game[i] >= 'a' && game[i] <= 'h')
		m.piece = PAWN;
	else
	{
		if (game[i] == 'N')
			m.piece = KNIGHT;
		else if (game[i] == 'B')
			m.piece = BISHOP;
		else if (game[i] == 'R')
			m.piece = ROOK;
		else if (game[i] == 'Q')
			m.piece = QUEEN;
		else if (game[i] == 'K')
			m.piece = KING;
		else
			m.piece = NONE;
		i++;
	}
	i = start;
	// is there an hint ? (N/R/B/Q) //TODO ! //Buggy
	if (m.piece == ROOK || m.piece == BISHOP || m.piece == KNIGHT || m.piece == QUEEN)
	{
		while (game[i] && game[i] != ' ')
			i++;
		while (ft_isdigit(game[i]) == 0)
			i--;
		i -= 2;
		if (game[i] == 'x')
			i--;
		if (ft_isdigit(game[i]) == 1)
			m.row_hint = game[i];
		else if (game[i] >= 'a' && game[i] <= 'h')
			m.col_hint = game[i];
		i--;
		if (i != start && game[i] >= 'a' && game[i] <= 'h')
			m.col_hint = game[i];
	}
	else //Tous les autres cas on n'aura pas d'indice ? cas particulier du pion ?
	{
		m.row_hint = '\0';
		m.col_hint = '\0';
	}
	i = start;
	// Double hint to do !
	// On récupère la destination
	if (m.type == NORMAL || m.type == CAPTURE)
	{
		while (game[i] != ' ')
			i++;
		while (ft_isdigit(game[i]) == 0)
			i--;
		m.destination[0] = game[i - 1];
		m.destination[1] = game[i];
		m.destination[2] = '\0'; 

	}
	i = start;
	while (game[i] != ' ')
		i++;
	if (game[i + 1] == '{')
	{
		while (game[i] != '%')
			i++;
		start = i + 1;
		while (game[i] != ']')
			i++;
		m.eval = ft_substr(game, start, i - start);
	}
	else
		m.eval = NULL;
	return (m);
}

int	split_moves(char *game, game_info *game_info, size_t len)
{
	move	m;
	int		nb_moves;
	move	*moves;
	int		i;
	int		j;

	nb_moves = 0;
	while ((len > 0) && (game[len] != ' ' || game[len - 1] != '.'))
		len--;
	// cas particuliers a gérer ici
	while (ft_isdigit(game[len]) == 0 && len > 0)
		len--;
	while (ft_isdigit(game[len]) == 1 && len > 0)
		len--;
	nb_moves = game[len + 1] - '0';
	len++;
	while (ft_isdigit(game[len + 1]) == 1 && len > 0)
	{
		nb_moves = nb_moves * 10 + game[len + 1] - '0';
		len++;
	}
	game_info->nb_moves = nb_moves * 2;
	moves = malloc(sizeof(move) * nb_moves * 2 + 1);
	i = 0;
	j = 0;
	while (j < nb_moves * 2)
	{
		// Gerer les cas particuliers avant !
		// Si ca merde sur les roques c'est ici
		while (ft_isalpha(game[i]) == 0 && game[i] != 'O')
			i++;
		moves[j] = parse_moves(game, i);
		j++;
		while (game[i] != ' ')
			i++;
		i++;
		if (game[i] == '{')
		{
			while (game[i] != '}')
				i++;
			i += 2;
			while (game[i] != ' ')
				i++;
		}
	}
	game_info->moves = malloc(sizeof(move) * nb_moves * 2);
	i = 0;
	while (i < nb_moves * 2)
	{
		game_info->moves[i] = moves[i];
		i++;
	}
	// debug
	// i = 0;
	// while (i < nb_moves * 2 && i < 5)
	// {	
	// 	printf("moves[%d]\n", i);
	// 	printf("pgn = %s\n", game_info->moves[i].pgn);
	// 	printf("eval : %s\n", game_info->moves[i].eval);
	// 	printf("comment : %s\n", game_info->moves[i].comment);
	// 	printf("dest : %s\n", game_info->moves[i].destination);
	// 	printf("col_hint : %c\n", game_info->moves[i].col_hint);
	// 	printf("row_hint : %c\n", game_info->moves[i].row_hint);
	// 	printf("is_check : %d\n", game_info->moves[i].is_check);
	// 	printf("is_mate : %d\n\n", game_info->moves[i].is_mate);
	// 	i++;
	// }
	free(moves);
	return (0);
}

void	split_game_infos(char *game, game_info *game_info, size_t len)
{
	int		nb_headers;
	char	**headers;
	int		i;
	int		j;
	int		start;
	char	*moves;

	split_headers(game, game_info);
	i = 1;
	while (!(game[i] == '\n' && game[i - 1] == '\n'))
		i++;
	i++;
	start = i;
	while (game[i] != '\n')
		i++;
	moves = ft_substr(game, start, i - start);
	split_moves(moves, game_info, ft_strlen(moves));
	// printf("len game = %d\n", ft_strlen(game));
	// parse_moves(game, game_info, ft_strlen(game));
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

	// opening file with game(s)
	fd = open("gametest2.txt", O_RDONLY); // Ajouter une option argv
	if (fd < 0)
	{
		printf("Error while opening a file\n");
		return (-1);
	}
	// getting a char * with headers and moves + filling game_info->headers
	game = get_game(fd, game_number);
	// spliting moves in a tab of structs inside game_info struct
	split_game_infos(game, game_info, ft_strlen(game));
	free(game);
	if (close(fd) < 0)
	{
		printf("Error while closing a file\n");
	}
	return (0);
}