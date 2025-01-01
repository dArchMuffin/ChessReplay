#include "header.h"
#include <stdio.h>

int	clean_line_col(char p, char y, char x, int board[8][8])
{
	char	start_x;

	start_x = x;
	// col up
	while (x < 7)
	{
		x++;
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	// col down
	x = start_x;
	while (x > 0)
	{
		x--;
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	return (1);
}

int	clean_line_row(char p, char y, char x, int board[8][8])
{
	char	start_y;

	start_y = y;
	// in row left
	while (y > 0)
	{
		y--;
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	y = start_y;
	// in row right
	while (y < 7)
	{
		y++;
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	return (1);
}

int	clean_piece_in_lines(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	if (move_idx % 2 != 0)
		p -= 32;
	if (clean_line_col(p, y, x, board) && clean_line_row(p, y, x, board))
		return (1);
	else
		return (0);
	return (1);
}