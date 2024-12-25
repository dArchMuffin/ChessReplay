#include "header.h"
#include <unistd.h>

void	init_board(int board[8][8])
{
	char	*black_pieces;
	char	*white_pieces;
	int		x;
	int		y;

	black_pieces = "RNBQKBNR";
	white_pieces = "rnbqkbnr";
	y = 7;
	while (y >= 0)
	{
		x = 0;
		while (x <= 7)
		{
			if (y == 7)
				board[y][x] = black_pieces[x];
			else if (y == 0)
				board[y][x] = white_pieces[x];
			else if (y == 6)
				board[y][x] = 'P';
			else if (y == 1)
				board[y][x] = 'p';
			else
				board[y][x] = ' ';
			x++;
		}
		y--;
	}
}

void	print_board(int board[8][8], game_info *game_info)
{
	int		x;
	int		y;
	char	row;
	char	col;
	int		headers;

	y = 7;
	headers = 0;
	row = '8';
	col = 'a';
	write(1, "  ||", 4);
	while (col <= 'h')
	{
		write(1, "  ", 2);
		write(1, &col, 1);
		write(1, " |", 2);
		col++;
	}
	write(1, "|", 1);
	write(1, "\n==++====+====+====+====+====+====+====+====++==\n", 50);
	while (y >= 0)
	{
		while (row >= '1')
		{
			write(1, &row, 1);
			write(1, " ||", 3);
			x = 0;
			while (x <= 7)
			{
				write(1, "  ", 2);
				write(1, &board[y][x], 1);
				write(1, " |", 2);
				x++;
			}
			write(1, "| ", 2);
			write(1, &row, 1);
			write(1, "\t", 1);
			if (headers < game_info->nb_headers)
				write(1, game_info->headers[headers],
					ft_strlen(game_info->headers[headers]));
			write(1, "\n", 1);
			headers++;
			if (y > 0)
				write(1, "--++----+----+----+----+----+----+----+----++--", 47);
			else
				write(1, "==++====+====+====+====+====+====+====+====++==",
					48);
			y--;
			write(1, "\t", 1);
			if (headers < game_info->nb_headers)
				write(1, game_info->headers[headers],
					ft_strlen(game_info->headers[headers]));
			write(1, "\n", 1);
			headers++;
			row--;
		}
	}
	col = 'a';
	write(1, "  ||", 4);
	while (col <= 'h')
	{
		write(1, "  ", 2);
		write(1, &col, 1);
		write(1, " |", 2);
		col++;
	}
	write(1, "|", 1);
	write(1, "\n", 1);
}

void	put_piece_in(piece_type piece, int board[8][8], char *dest, int color)
{
	dest[1] = dest[1] - '0' - 1;
	dest[0] = dest[0] - 'a';
	if (piece == PAWN)
		board[dest[1]][dest[0]] = 'p';
	else if (piece == ROOK)
		board[dest[1]][dest[0]] = 'r';
	else if (piece == KNIGHT)
		board[dest[1]][dest[0]] = 'n';
	else if (piece == BISHOP)
		board[dest[1]][dest[0]] = 'b';
	else if (piece == QUEEN)
		board[dest[1]][dest[0]] = 'q';
	else if (piece == KING)
		board[dest[1]][dest[0]] = 'k';
	if (color % 2 == 0)
		board[dest[1]][dest[0]] - 32; // ICI !
}

void	no_hint_case(game_info *infos, int board[8][8], char p, int color)
{
	if (infos->moves[color].piece == KNIGHT && !(infos->moves[color].row_hint)
		&& !(infos->moves[color].col_hint))
	{
		// Chercher un n / N dans l'une des cases à portée de dest
		// y + 2 x + 1
		// y + 2 x - 1
		// y - 2 x + 1
		// y - 2 x - 1
		// y + 1 x + 2
		// y - 1 x + 2
		// y + 1 x - 2
		// y - 1 x - 2
		// board[y][x] = ' ';
	}
	if (infos->moves[color].piece == ROOK && !(infos->moves[color].row_hint)
		&& !(infos->moves[color].col_hint))
	{
		// Chercher un c dans l'une des cases à portée de dest
		// y x + i
		// y + i x
		// board[y][x] = ' ';
	}
	if (infos->moves[color].piece == BISHOP && !(infos->moves[color].row_hint)
		&& !(infos->moves[color].col_hint))
	{
		// Chercher un c dans l'une des cases à portée de dest
		// y - i x - i
		// y + i x + i
		// y - i x + i
		// y + i x - i
		// board[y][x] = ' ';
	}
	if (infos->moves[color].piece == QUEEN && !(infos->moves[color].row_hint)
		&& !(infos->moves[color].col_hint))
	{
		// Chercher un c dans l'une des cases à portée de dest
		// y - i x - i
		// y + i x + i
		// y - i x + i
		// y + i x - i
		// y x + i
		// y + i x
		// board[y][x] = ' ';
	}
	if (infos->moves[color].piece == KING && !(infos->moves[color].row_hint)
		&& !(infos->moves[color].col_hint))
	{
		// Chercher un c dans l'une des cases à portée de dest
		// x + 1 y
		// x - 1 y
		// x y + 1
		// x y - 1
		// x + 1 y + 1
		// x + 1 y - 1
		// x - 1 y + 1
		// x - 1 y - 1
		// board[y][x] = ' ';
	}
}

void	clean_origin(game_info *infos, int board[8][8], int color)
{
	char	p;

	// p = board[dest[1] dest[0]];
	if (infos->moves[color].piece == PAWN)
	{
		// chercher un p dans la col pgn[0]
		// ori[0] = y
		// ori[1] = x
		// board[y][x] = ' ';
	}
	// Cases without any hint
	if (!(infos->moves[color].col_hint) && !(infos->moves[color].row_hint))
		return (no_hint_case(infos, board, p, color));
	// Si double hint / superful ?
	if (infos->moves[color].col_hint && infos->moves[color].row_hint)
		board[infos->moves[color].col_hint][infos->moves[color].row_hint] = ' ';
	// Si hint col
	else if (infos->moves[color].col_hint)
	{
		// Chercher un p dans board[col_hint][?]
		// ori[0] = col_hint
		// ori[1] = x
		// board[y][x] = ' ';
	}
	// si hint row
	else if (infos->moves[color].row_hint)
	{
		// Chercher un p dans board[?][row_hint]
		// ori[0] = y
		// ori[1] = row_hint
		// board[y][x] = ' ';
	}
}

void	update_board(game_info *infos, int board[8][8], int color)
{
	put_piece_in(infos->moves[color].piece, board,
		infos->moves[color].destination, color);
	clean_origin(infos, board, color);
}