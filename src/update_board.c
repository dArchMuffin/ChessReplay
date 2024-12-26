#include "header.h"
#include <stdio.h> //libft

void	put_piece_in(game_info *infos, int board[8][8], int move_idx)
{
	char	dest[2];

	dest[0] = infos->moves[move_idx].destination[0] - 'a';
	dest[1] = infos->moves[move_idx].destination[1] - 1 - '0';
	if (infos->moves[move_idx].piece == PAWN)
		board[dest[1]][dest[0]] = 'p';
	if (infos->moves[move_idx].piece == ROOK)
		board[dest[1]][dest[0]] = 'r';
	if (infos->moves[move_idx].piece == KNIGHT)
		board[dest[1]][dest[0]] = 'n';
	if (infos->moves[move_idx].piece == BISHOP)
		board[dest[1]][dest[0]] = 'b';
	if (infos->moves[move_idx].piece == QUEEN)
		board[dest[1]][dest[0]] = 'q';
	if (infos->moves[move_idx].piece == KING)
		board[dest[1]][dest[0]] = 'k';
	if (move_idx % 2 != 0)
		board[infos->moves[move_idx].destination[1] - '0'
			- 1][infos->moves[move_idx].destination[0] - 'a'] -= 32;
}

void	no_hint_case(game_info *infos, int board[8][8], int move_idx)
{
	if (infos->moves[move_idx].piece == KNIGHT)
	{
		if (clean_knight('n', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : KNIGHT not found !\n");
	}
	if (infos->moves[move_idx].piece == ROOK)
	{
		if (clean_piece_in_lines('r', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : ROOK not found !\n");
	}
	if (infos->moves[move_idx].piece == BISHOP)
	{
		if (clean_piece_in_diags('b', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : BISHOP not found !\n"); // no found
	}
	if (infos->moves[move_idx].piece == QUEEN)
	{
		if (clean_piece_in_diags('q', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			if (clean_piece_in_lines('q', infos->moves[move_idx].destination[0],
					infos->moves[move_idx].destination[1], board,
					move_idx) == 1)
				printf("ERROR : QUEEN not found !\n");
	}
	if (infos->moves[move_idx].piece == KING)
	{
		if (clean_king('k', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : KING not found !\n");
	}
}

void	col_hint_case(game_info *infos, int board[8][8], int move_idx)
// edge case pawn ?
{
	int y;
	int x;
	char p;

	if (infos->moves[move_idx].piece == KNIGHT)
	{
		p = 'n';
		if (move_idx % 2 != 0)
			p -= 32;
		y = infos->moves[move_idx].col_hint - 'a';
		x = infos->moves[move_idx].destination[1] - '0' - 1;
		printf("%d\n", infos->moves[move_idx].destination[0] - 'a' - y);
		if ((infos->moves[move_idx].destination[0] - 'a') - y == -2)
		{
			printf("board[%d][%d] = %c\n", x - 1, y, board[x - 1][y]);
			if (board[x - 1][y] == p)
			{
				board[x - 1][y] = ' ';
				return ;
			}
			printf("board[%d][%d] = %c\n", x + 1, y, board[x + 1][y]);
			if (board[x + 1][y] == p)
			{
				board[x + 1][y] = ' ';
				return ;
			}
		}
		if ((infos->moves[move_idx].destination[0] - 'a') - y == -1)
		{
			if (board[x + 2][y] == p)
			{
				board[x + 2][y] = ' ';
				return ;
			}
			if (board[x - 2][y] == p)
			{
				board[x - 2][y] = ' ';
				return ;
			}
		}
		if ((infos->moves[move_idx].destination[0] - 'a') - y == 1)
		{
			if (board[x + 2][y] == p)
			{
				board[x + 2][y] = ' ';
				return ;
			}
			if (board[x - 2][y] == p)
			{
				board[x - 2][y] = ' ';
				return ;
			}
		}
		if ((infos->moves[move_idx].destination[0] - 'a') - y == 2)
		{
			printf("board[%d][%d] = %c\n", x + 1, y, board[x + 1][y]);
			if (board[x + 1][y] == p)
			{
				board[x + 1][y] = ' ';
				return ;
			}
			printf("board[%d][%d] = %c\n", x - 1, y, board[x - 1][y]);
			if (board[x - 1][y] == p)
			{
				board[x - 1][y] = ' ';
				return ;
			}
		}
	}
	if (infos->moves[move_idx].piece == ROOK)
	{
		p = 'r';
		if (move_idx % 2 != 0)
			p -= 32;
		y = infos->moves[move_idx].col_hint - 'a';
		x = 0;
		while (x <= 7)
		{
			if (board[x][y] == p)
			{
				board[x][y] = ' ';
				return ;
			}
			x++;
		}
	}
	if (infos->moves[move_idx].piece == BISHOP)
	{
		p = 'b';
		if (move_idx % 2 != 0)
			p -= 32;
	}
	if (infos->moves[move_idx].piece == QUEEN)
	{
		p = 'q';
		if (move_idx % 2 != 0)
			p -= 32;
	}
}

void	row_hint_case(game_info *infos, int board[8][8], int move_idx)
// edge case pawn ?
{
	if (infos->moves[move_idx].piece == KNIGHT)
	{
		if (clean_knight('n', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : KNIGHT not found !\n");
	}
	if (infos->moves[move_idx].piece == ROOK)
	{
		if (clean_piece_in_lines('r', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : ROOK not found !\n");
	}
	if (infos->moves[move_idx].piece == BISHOP)
	{
		if (clean_piece_in_diags('b', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			printf("ERROR : BISHOP not found !\n"); // no found
	}
	if (infos->moves[move_idx].piece == QUEEN)
	{
		if (clean_piece_in_diags('q', infos->moves[move_idx].destination[0],
				infos->moves[move_idx].destination[1], board, move_idx) == 1)
			if (clean_piece_in_lines('q', infos->moves[move_idx].destination[0],
					infos->moves[move_idx].destination[1], board,
					move_idx) == 1)
				printf("ERROR : QUEEN not found !\n");
	}
}

void	update_board(game_info *infos, int board[8][8], int move_idx)
{
	clean_origin(infos, board, move_idx);
	put_piece_in(infos, board, move_idx);
}