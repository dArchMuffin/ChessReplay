#include "header.h"
#include <stdio.h>

int	clean_diag_top(char p, char y, char x, int board[8][8])
{
	char	start_y;
	char	start_x;

	start_y = y;
	start_x = x;
	while (y < 7 && x < 7)
	{
		y++;
		x++;
		// printf("diag top right : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	y = start_y;
	x = start_x;
	while (y > 0 && x < 7)
	{
		y--;
		x++;
		// printf("diag top left : board[%d][%d] = %c\n", x, y, board[x][y]);
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

int	clean_diag_bot(char p, char y, char x, int board[8][8])
{
	char	start_y;
	char	start_x;

	start_y = y;
	start_x = x;
	// diag bot left
	while (y > 0 && x > 0)
	{
		y--;
		x--;
		// printf("diag bot left : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	y = start_y;
	x = start_x;
	while (y < 7 && x > 0)
	{
		y++;
		x--;
		// printf("diag bot right : board[%d][%d] = %c\n", x, y, board[x][y]);
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

int	clean_piece_in_diags(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int y;
	int x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	if (move_idx % 2 != 0)
		p -= 32;
	if (clean_diag_bot(p, y, x, board) && clean_diag_top(p, y, x, board))
		return (1);
	else
		return (0);
}