#include "header.h"
#include <stdio.h> //libft

int	clean_knight(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	// printf("x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
	if (x - 2 >= 0 && y + 1 <= 7)
	{
		if (board[x - 2][y + 1] == p)
		{
			board[x - 2][y + 1] = ' ';
			return (0);
		}
	}
	if (x - 2 >= 0 && y - 1 >= 0)
	{
		if (board[x - 2][y - 1] == p)
		{
			board[x - 2][y - 1] = ' ';
			return (0);
		}
	}
	if (x + 2 <= 7 && y + 1 <= 7)
	{
		if (board[x + 2][y + 1] == p)
		{
			board[x + 2][y + 1] = ' ';
			return (0);
		}
	}
	if (x + 2 <= 7 && y - 1 >= 0)
	{
		if (board[x + 2][y - 1] == p)
		{
			board[x + 2][y - 1] = ' ';
			return (0);
		}
	}
	if (x + 1 <= 7 && y - 2 >= 0)
	{
		if (board[x + 1][y - 2] == p)
		{
			board[x + 1][y - 2] = ' ';
			return (0);
		}
	}
	if (x - 1 >= 0 && y - 2 >= 0)
	{
		if (board[x - 1][y - 2] == p)
		{
			board[x - 1][y - 2] = ' ';
			return (0);
		}
	}
	if (x + 1 <= 7 && y + 2 <= 7)
	{
		if (board[x + 1][y + 2] == p)
		{
			board[x + 1][y + 2] = ' ';
			return (0);
		}
	}
	if (x - 1 >= 0 && y + 2 <= 7)
	{
		if (board[x - 1][y + 2] == p)
		{
			board[x - 1][y + 2] = ' ';
			return (0);
		}
	}
}
// invalid read of size ?
int	clean_king(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	printf("x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
	x = x - 1;
	y = y - 1;
	// 3 cases du bas en ligne
	while (y <= start_y - 'a' + 1)
	{
		// printf("3 bot cells : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y++;
	}
	x = start_x - '0' - 1;
	y = start_y - 'a' - 1;
	// 3 cases du milieu en ligne
	while (y <= start_y - 'a' + 1)
	{
		// printf("3 middle cells : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y++;
	}
	x = start_x - '0';
	y = start_y - 'a' - 1;
	// 3 cases du haut en ligne
	while (y <= start_y - 'a' + 1)
	{
		// printf("3 upper cells : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y++;
	}
}

int	clean_piece_in_lines(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	// printf("x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
	// in col up
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
	// in col down
	x = start_x - '0' - 1;
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
	x = start_x - '0' - 1;
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
	y = start_y - 'a';
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
	printf("%c not found in lines\n", p);
	return (1);
}

int	clean_piece_in_diags(char p, char start_y, char start_x, int board[8][8],
							int move_idx) // A racourcir ! //ajouter le insight
{
	int y;
	int x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	printf("x = %d | y = %d\n target : board[3][2] = %c\n", x, y, board[3][2]);
	if (move_idx % 2 != 0)
		p -= 32;
	// diag bot left
	while (y > 0 && x > 0)
	{
		y--;
		x--;
		printf("diag bot left : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	y = start_y - 'a';
	x = start_x - '0' - 1;
	// diag top right
	while (y < 7 && x < 7)
	{
		y++;
		x++;
		printf("diag top right : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	y = start_y - 'a';
	x = start_x - '0' - 1;
	// diag top left
	while (y > 0 && x < 7)
	{
		y--;
		x++;
		printf("diag top left : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	y = start_y - 'a';
	x = start_x - '0' - 1;
	// diag bot right
	while (y < 7 && x > 0)
	{
		y++;
		x--;
		printf("diag bot right : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] != ' ' && board[x][y] != p)
			break ;
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
	}
	printf("%c not found in diag\n", p);
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
	{
		return (col_hint_case(infos, board, move_idx));
		// Chercher un p dans board[col_hint][?]
		// ori[0] = col_hint
		// ori[1] = x
		// board[y][x] = ' ';
	}
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