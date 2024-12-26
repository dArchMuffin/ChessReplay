#include "header.h"
#include <stdio.h> //A VIRER !
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
				write(1, "==++====+====+====+====+====+====+====+====++==", 48);
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
	write(1, "|\n", 2);
}

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

int	clean_knight(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	printf("x = %d | y = %d\n", x, y);
	printf("target : board[1][5] = %c\n", board[1][5]);
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
		printf("3 cases du bas: board[%d][%d] = %c\n", x, y, board[x][y]);
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
		printf("3 cases du milieu : board[%d][%d] = %c\n", x, y, board[x][y]);
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
		printf("3 cases du haut : board[%d][%d] = %c\n", x, y, board[x][y]);
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
	printf("x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
	// in col
	y = 0;
	while (y <= 7)
	{
		printf("col y+ : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y++;
	}
	y = start_y - 'a';
	// in row
	x = 0;
	while (x <= 7)
	{
		printf("row x+ : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		x++;
	}
	printf("%c not found in lines\n", p);
	return (1);
}

int	clean_piece_in_diags(char p, char start_y, char start_x, int board[8][8],
							int move_idx) // A racourcir !
{
	int y;
	int x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	printf("x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
	// diag bot left
	while (y >= 0 && x >= 0)
	{
		printf("diag bot left x- y- : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y--;
		x--;
	}
	y = start_y - 'a';
	x = start_x - '0' - 1;
	// diag top right
	while (y <= 7 && x <= 7)
	{
		printf("diag top right x+ y+ : board[%d][%d] = %c\n", x, y,
			board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y++;
		x++;
	}
	y = start_y - 'a';
	x = start_x - '0' - 1;
	// diag top left
	while (y >= 0 && x <= 7)
	{
		printf("diag top left x+ y- : board[%d][%d] = %c\n", x, y, board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y--;
		x++;
	}
	y = start_y - 'a';
	x = start_x - '0' - 1;
	// diag bot right
	while (y <= 7 && x >= 0)
	{
		printf("diag bot right x- y+ : board[%d][%d] = %c\n", x, y,
			board[x][y]);
		if (board[x][y] == p)
		{
			board[x][y] = ' ';
			return (0);
		}
		y++;
		x--;
	}
	printf("%c not found in diag\n", p);
	return (1);
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

void(col_hint_case(game_info *infos, int board[8][8], int move_idx))
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

void(row_hint_case(game_info *infos, int board[8][8], int move_idx))
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

void	clean_origin(game_info *infos, int board[8][8], int move_idx)
{
	char	p;
	int		x;
	int		y;

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
	// Si hint col
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

void	update_board(game_info *infos, int board[8][8], int move_idx)
{
	clean_origin(infos, board, move_idx);
	put_piece_in(infos, board, move_idx);
}