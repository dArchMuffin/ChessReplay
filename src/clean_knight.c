#include <stdio.h> //libft

int	clean_knight_bot(char p, char y, char x, int board[8][8])
{
	// printf("clening knight bot\n");
	if (x - 2 >= 0 && y + 1 <= 7 && board[x - 2][y + 1] == p)
	{
		// printf("board[%d][%d] = %c\n", x - 2, y + 1, board[x-2][y+1]);
		board[x - 2][y + 1] = ' ';
		return (0);
	}
	if (x - 2 >= 0 && y - 1 >= 0 && board[x - 2][y - 1] == p)
	{
		board[x - 2][y - 1] = ' ';
		return (0);
	}
	return (1);
}

int	clean_knight_top(char p, char y, char x, int board[8][8])
{
	if (x + 2 <= 7 && y + 1 <= 7 && board[x + 2][y + 1] == p)
	{
		// printf("board[%d][%d] = %c\n", x + 2, y + 1, board[x+2][y+1]);
		board[x + 2][y + 1] = ' ';
		return (0);
	}
	if (x + 2 <= 7 && y - 1 >= 0 && board[x + 2][y - 1] == p)
	{
		board[x + 2][y - 1] = ' ';
		return (0);
	}
	return (1);
}

int	clean_knight_left(char p, char y, char x, int board[8][8])
{
	if (x + 1 <= 7 && y - 2 >= 0 && board[x + 1][y - 2] == p)
	{
		board[x + 1][y - 2] = ' ';
		return (0);
	}
	if (x - 1 >= 0 && y - 2 >= 0 && board[x - 1][y - 2] == p)
	{
		board[x - 1][y - 2] = ' ';
		return (0);
	}
	return (1);
}

int	clean_knight_right(char p, char y, char x, int board[8][8])
{
	if (x + 1 <= 7 && y + 2 <= 7 && board[x + 1][y + 2] == p)
	{
		board[x + 1][y + 2] = ' ';
		return (0);
	}
	if (x - 1 >= 0 && y + 2 <= 7 && board[x - 1][y + 2] == p)
	{
		board[x - 1][y + 2] = ' ';
		return (0);
	}
	return(1);
}

int	clean_knight(char p, char start_y, char start_x, int board[8][8],
		int move_idx)
{
	int	y;
	int	x;

	y = start_y - 'a';
	x = start_x - '0' - 1;
	// printf("KNIGHT Cleaning : x = %d | y = %d\n", x, y);
	if (move_idx % 2 != 0)
		p -= 32;
		if (clean_knight_bot(p, y, x, board) 
		&& clean_knight_left(p, y, x, board) 
		&& clean_knight_right(p, y, x, board) 
		&& clean_knight_top(p, y, x, board))
		{
			printf("Error cleaning knight\n");
			return (1);
		}	
		else 
			return(0);
}