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
	int x;
	int y;
	char row;
	char col;
	int headers;

	y = 7;
	headers = 0;
	row = '8';
	col = 'a';
	write(1, "  |", 3);
	while (col <= 'h')
	{
		write(1, "  ", 2);
		write(1, &col, 1);
		write(1, " |", 2);
		col++;
	}
	write(1, "\n--+----+----+----+----+----+----+----+----+--\n", 47);
	while (y >= 0)
	{
		while (row >= '1')
		{
			write(1, &row, 1);
			write(1, " |", 2);
			x = 0;
			while (x <= 7)
			{
				write(1, "  ", 2);
				write(1, &board[y][x], 1);
				write(1, " |", 2);
				x++;
			}
			y--;
			write(1, " ", 1);
			write(1, &row, 1);
			write(1, "\t", 1);
			write(1, game_info->headers[headers],
				ft_strlen(game_info->headers[headers]));
			headers++;
			write(1, "--+----+----+----+----+----+----+----+----+--", 45);
			write(1, "\t", 1);
			write(1, game_info->headers[headers],
				ft_strlen(game_info->headers[headers]));
			headers++;
			row--;
		}
	}
	col = 'a';
	write(1, "  | ", 4);
	while (col <= 'h')
	{
		write(1, &col, 1);
		write(1, "  | ", 5);
		col++;
	}
	write(1, "\n", 1);
}