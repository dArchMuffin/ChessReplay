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
		if ((infos->moves[move_idx].destination[0] - 'a') - y == -2)
		{
			// printf("board[%d][%d] = %c\n", x - 1, y, board[x - 1][y]);
			if (board[x - 1][y] == p)
			{
				board[x - 1][y] = ' ';
				return ;
			}
			// printf("board[%d][%d] = %c\n", x + 1, y, board[x + 1][y]);
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
			// printf("board[%d][%d] = %c\n", x + 1, y, board[x + 1][y]);
			if (board[x + 1][y] == p)
			{
				board[x + 1][y] = ' ';
				return ;
			}
			// printf("board[%d][%d] = %c\n", x - 1, y, board[x - 1][y]);
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
	if (infos->moves[move_idx].piece == QUEEN)
	{
		p = 'q';
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
		}
	}
}

void	row_hint_case(game_info *infos, int board[8][8], int move_idx)
{
	int y;
	int x;
	char p;

	if (infos->moves[move_idx].piece == KNIGHT)
	{
		p = 'n';
		if (move_idx % 2 != 0)
			p -= 32;
		y = infos->moves[move_idx].destination[0] - 'a';
		x = infos->moves[move_idx].row_hint - '0' - 1;
		if ((infos->moves[move_idx].destination[1] - '0' - 1) - x == -2)
		{
			// printf("board[%d][%d] = %c\n", x, y - 1, board[x][y - 1]);
			if (board[x][y - 1] == p)
			{
				board[x][y - 1] = ' ';
				return ;
			}
			// printf("board[%d][%d] = %c\n", x, y + 1, board[x][y + 1]);
			if (board[x][y + 1] == p)
			{
				board[x][y + 1] = ' ';
				return ;
			}
		}
		if ((infos->moves[move_idx].destination[1] - '0' - 1) - x == -1)
		{
			// printf("board[%d][%d] = %c\n", x, y + 2, board[x][y + 2]);
			if (board[x][y + 2] == p)
			{
				board[x][y + 2] = ' ';
				return ;
			}
			// printf("board[%d][%d] = %c\n", x, y - 2, board[x][y- 2]);
			if (board[x][y - 2] == p)
			{
				board[x][y - 2] = ' ';
				return ;
			}
		}
		if ((infos->moves[move_idx].destination[1] - '0' - 1) - x == 1)
		{
			// printf("board[%d][%d] = %c\n", x, y + 2, board[x][y + 2]);
			if (board[x][y + 2] == p)
			{
				board[x][y + 2] = ' ';
				return ;
			}
			// printf("board[%d][%d] = %c\n", x, y - 2, board[x][y - 2]);
			if (board[x][y - 2] == p)
			{
				board[x][y - 2] = ' ';
				return ;
			}
		}
		if ((infos->moves[move_idx].destination[1] - '0' - 1) - x == 2)
		{
			// printf("board[%d][%d] = %c\n", x, y + 1, board[x][y + 1]);
			if (board[x][y + 1] == p)
			{
				board[x][y + 1] = ' ';
				return ;
			}
			// printf("board[%d][%d] = %c\n", x, y - 1, board[x][y - 1]);
			if (board[x][y - 1] == p)
			{
				board[x][y - 1] = ' ';
				return ;
			}
		}
	}
	if (infos->moves[move_idx].piece == ROOK)
	{
		p = 'r';
		if (move_idx % 2 != 0)
			p -= 32;
		y = 0;
		x = infos->moves[move_idx].col_hint - '0' - 1;
		while (y <= 7)
		{
			if (board[x][y] == p)
			{
				board[x][y] = ' ';
				return ;
			}
			y++;
		}
	}
	if (infos->moves[move_idx].piece == BISHOP)
	{
		p = 'b';
		if (move_idx % 2 != 0)
			p -= 32;
		y = 0;
		x = infos->moves[move_idx].col_hint - '0' - 1;
		while (y <= 7)
		{
			if (board[x][y] == p)
			{
				board[x][y] = ' ';
				return ;
			}
			y++;
		}
	}
	if (infos->moves[move_idx].piece == QUEEN)
	{
		p = 'q';
		if (move_idx % 2 != 0)
			p -= 32;
		y = 0;
		x = infos->moves[move_idx].col_hint - '0' - 1;
		while (y <= 7)
		{
			if (board[x][y] == p)
			{
				board[x][y] = ' ';
				return ;
			}
			y++;
		}
	}
}

int	castle_cases(game_info *infos, int board[8][8], int move_idx)
{
	if (infos->moves[move_idx].type == SHORT_CASTLE)
	{
		if (move_idx % 2 == 0)
		{
			board[0][4] = ' ';
			board[0][7] = ' ';
			board[0][6] = 'k';
			board[0][5] = 'r';
		}
		else
		{
			board[7][4] = ' ';
			board[7][7] = ' ';
			board[7][6] = 'K';
			board[7][5] = 'R';
		}
	}
	else
	{
		if (move_idx % 2 == 0)
		{
			board[0][0] = ' ';
			board[0][4] = ' ';
			board[0][2] = 'k';
			board[0][3] = 'r';
		}
		else
		{
			board[7][0] = ' ';
			board[7][4] = ' ';
			board[7][2] = 'K';
			board[7][3] = 'R';
		}
	}
}

int	promote_and_clean(game_info * infos, int board[8][8], int move_idx)
{
	int x;
	int y;

	if (infos->moves[move_idx].is_promotion == true)
	{
		if (move_idx % 2 == 0)
		{
			if (infos->moves[move_idx].type == CAPTURE)
			{
				x = infos->moves[move_idx].destination[1] - '0' - 1;
				y = infos->moves[move_idx].pgn[0] - 'a';
				board[x - 1][y] = ' ';
				if (infos->moves[move_idx].promoted == KNIGHT)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'n';	
				else if (infos->moves[move_idx].promoted == BISHOP)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'b';	
				else if (infos->moves[move_idx].promoted == ROOK)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'r';	
				else if (infos->moves[move_idx].promoted == QUEEN)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'q';	
			}
			else 
			{
				board[infos->moves[move_idx].pgn[1] - '0' - 2][infos->moves[move_idx].pgn[0] - 'a'] = ' ';
				if (infos->moves[move_idx].promoted == KNIGHT)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'n';	
				else if (infos->moves[move_idx].promoted == BISHOP)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'b';	
				else if (infos->moves[move_idx].promoted == ROOK)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'r';	
				else if (infos->moves[move_idx].promoted == QUEEN)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'q';	
			}
		}
		else
		{
			if (infos->moves[move_idx].type == CAPTURE)
			{
				x = infos->moves[move_idx].destination[1] - '0' - 1;
				y = infos->moves[move_idx].pgn[0] - 'a';
				board[x + 1][y] = ' ';
				if (infos->moves[move_idx].promoted == KNIGHT)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'N';	
				else if (infos->moves[move_idx].promoted == BISHOP)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'B';	
				else if (infos->moves[move_idx].promoted == ROOK)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'R';	
				else if (infos->moves[move_idx].promoted == QUEEN)
				board[x][infos->moves[move_idx].destination[0] - 'a'] = 'Q';	
			}
			else 
			{
				board[infos->moves[move_idx].pgn[1] - '0'][infos->moves[move_idx].pgn[0] - 'a'] = ' ';
				if (infos->moves[move_idx].promoted == KNIGHT)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'N';	
				else if (infos->moves[move_idx].promoted == BISHOP)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'B';	
				else if (infos->moves[move_idx].promoted == ROOK)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'R';	
				else if (infos->moves[move_idx].promoted == QUEEN)
				board[infos->moves[move_idx].pgn[1] - '0' - 1][infos->moves[move_idx].pgn[0] - 'a'] = 'Q';	
			}
		}
	}
}
void	update_board(game_info *infos, int board[8][8], int move_idx)
{
	if (infos->moves[move_idx].type == SHORT_CASTLE
		|| infos->moves[move_idx].type == LONG_CASTLE)
		castle_cases(infos, board, move_idx);
	else if (infos->moves[move_idx].is_promotion == true)
		promote_and_clean(infos, board, move_idx);
	else
	{
		clean_origin(infos, board, move_idx);
		put_piece_in(infos, board, move_idx);
	}
}
