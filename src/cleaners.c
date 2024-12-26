#include "header.h"
#include <stdio.h> //libft

// invalid read of size ?
int	clean_king(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	// printf("x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
	if (x - 1 >= 0)
		x = x - 1;
	while (x <= 7 && x <= x + 1)
	{
		y = 0;
		while (y <= 7 && y <= start_y - 'a' + 1)
		{
			// printf("3 bot cells : board[%d][%d] = %c\n", x, y, board[x][y]);
			if (board[x][y] == p)
			{
				board[x][y] = ' ';
				return (0);
			}
			y++;
		}
		x++;
	}
	printf("ERROR : %c not found\n", p);
	return (1);
}

void	clean_origin(game_info *infos, int board[8][8], int move_idx)
{
	char p;
	int x;
	int y;

	x = 0;
	y = 0;
	// p = board[dest[1] dest[0]];
	if (infos->moves[move_idx].piece == PAWN) // edge case prom : hint ?
	{
		p = 'p';
		y = infos->moves[move_idx].pgn[0] - 'a';
		if (move_idx % 2 != 0)
			p -= 32;
		while (x < 7)
		{
			if (board[x][y] == p)
			{
				board[x][y] = ' ';
				break ;
			}
			x++;
		}
	}
	// Cases without any hint
	if (!(infos->moves[move_idx].col_hint)
		&& !(infos->moves[move_idx].row_hint))
		return (no_hint_case(infos, board, move_idx));
	// Si double hint //TODO !
	if (infos->moves[move_idx].col_hint && infos->moves[move_idx].row_hint)
		board[infos->moves[move_idx].col_hint][infos->moves[move_idx].row_hint] = ' ';
	// Si hint col //To do !
	else if (infos->moves[move_idx].col_hint)
		return (col_hint_case(infos, board, move_idx));
	// si hint row
	else if (infos->moves[move_idx].row_hint)
	{
		return (row_hint_case(infos, board, move_idx));
		// Chercher un p dans board[?][row_hint]
		// ori[0] = y
		// ori[1] = row_hint
		// board[y][x] = ' ';
	}
}