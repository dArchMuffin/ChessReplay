#include "header.h"
#include "stdio.h" //A virer quand j'aurai mis mon printf

int	print_piece(game_info *infos, int move_idx)
{
	if (infos->moves[move_idx].piece == PAWN)
		printf("pawn ");
	else if (infos->moves[move_idx].piece == KNIGHT)
		printf("knight ");
	else if (infos->moves[move_idx].piece == BISHOP)
		printf("bishop ");
	else if (infos->moves[move_idx].piece == ROOK)
		printf("rook ");
	else if (infos->moves[move_idx].piece == QUEEN)
		printf("queen ");
	else if (infos->moves[move_idx].piece == KING)
		printf("king ");
}

void	print_piece_in(int board[8][8], char d[3], int move_idx) // To fix
{
	char dest[3];

	dest[2] = '\0';
	dest[1] = d[1] - '0' - 1;
	dest[0] = d[0] - 'a';
	if (board[dest[1]][dest[0]] == ' ')
	{
		if ((move_idx % 2 == 0 && board[dest[1] - 1][dest[0]] == 'P') || (move_idx % 2 != 0 && board[dest[1] + 1][dest[0]] == 'p'))
			printf("pawn ");
		else
			printf("[no piece found] ");
	}
	else if (board[dest[1]][dest[0]] == 'p' || board[dest[1]][dest[0]] == 'P')
		printf("pawn ");
	else if (board[dest[1]][dest[0]] == 'r' || board[dest[1]][dest[0]] == 'R')
		printf("rook ");
	else if (board[dest[1]][dest[0]] == 'n' || board[dest[1]][dest[0]] == 'N')
		printf("knight ");
	else if (board[dest[1]][dest[0]] == 'b' || board[dest[1]][dest[0]] == 'B')
		printf("bishop ");
	else if (board[dest[1]][dest[0]] == 'q' || board[dest[1]][dest[0]] == 'Q')
		printf("queen ");
	if (move_idx % 2 == 0 && board[dest[1] - 1][dest[0]] == 'P')
		printf("in %c%c", dest[0] + 'a', dest[1] + '0');
	else if (move_idx % 2 != 0 && board[dest[1] + 1][dest[0]] == 'p')
		printf("in %c%c", dest[0] + 'a', dest[1] + 2 + '0');
	else
		printf("in %c%c", dest[0] + 'a', dest[1] + 1 + '0');
}

int	*write_move(game_info *infos, int board[8][8], int move_idx)
{
	int i;
	if (infos->moves[move_idx].is_draw == true)
	{
		if (move_idx % 2 == 0)
			printf("\nDraw");
		else
			printf("\n\n\n\nDraw");
	}
	if (infos->moves[move_idx].is_time_out == true)
	{
		if (move_idx % 2 != 0) //!! paas sur
			printf("\nBlack's time out : white win\n\n");
		else
			printf("\nWhite's time out : black win\n\n");
		return (0);
	}
	if (move_idx % 2 == 0 && infos->moves[move_idx].is_draw != true)
		printf("\nWhite ");
	else if (infos->moves[move_idx].is_draw != true)
		printf("\n\n\n\n\nBlack ");
	if (infos->moves[move_idx].is_resign == true
		&& infos->moves[move_idx].is_mate == false)
	{
		if (move_idx % 2 == 0)
			printf("resign : black win");
		else
			printf("resign : white win");
	}
	if (infos->moves[move_idx].type == SHORT_CASTLE)
		printf("short castle");
	if (infos->moves[move_idx].type == LONG_CASTLE)
		printf("long castle");
	if (infos->moves[move_idx].is_promotion == true)
	{
		if (infos->moves[move_idx].type == CAPTURE)
		{
			printf("pawn takes ");
			print_piece_in(board, infos->moves[move_idx].destination, move_idx);
		}
		else if (infos->moves[move_idx].type == NORMAL)
		{
			printf("pawn moves in ");
			printf("%s", infos->moves[move_idx].destination);
		}
		printf(" and is promoted to ");
		if (infos->moves[move_idx].promoted == KNIGHT)
			printf("knight");
		else if (infos->moves[move_idx].promoted == BISHOP)
			printf("bishop");
		else if (infos->moves[move_idx].promoted == ROOK)
			printf("rook");
		else if (infos->moves[move_idx].promoted == QUEEN)
			printf("queen");
	}
	if (infos->moves[move_idx].is_promotion != true)
		print_piece(infos, move_idx);
	if (infos->moves[move_idx].type == NORMAL
		&& infos->moves[move_idx].is_resign != true
		&& infos->moves[move_idx].is_draw != true
		&& infos->moves[move_idx].is_promotion != true)
		printf("moves to %s", infos->moves[move_idx].destination);
	else if (infos->moves[move_idx].type == CAPTURE && infos->moves[move_idx].is_promotion != true && infos->moves[move_idx].is_resign != true)
	{
		printf("takes ");
		print_piece_in(board, infos->moves[move_idx].destination, move_idx);
	}
	else if (infos->moves[move_idx].type != LONG_CASTLE
		&& infos->moves[move_idx].type != SHORT_CASTLE
		&& infos->moves[move_idx].is_resign != true
		&& infos->moves[move_idx].is_draw != true
		&& infos->moves[move_idx].is_promotion != true)
		printf("error in type\n");
	if (infos->moves[move_idx].is_check == true)
		printf(". Check !");
	else if (infos->moves[move_idx].is_mate == true)
		printf(". Checkmate !");
	else if (infos->moves[move_idx].is_resign != true)
		printf(".");
	printf("\t #%d : [%s]", move_idx, infos->moves[move_idx].pgn);
	if (infos->moves[move_idx].is_mate == true)
	{
		if (move_idx % 2 == 0)
			printf("\nWhite win\n");
		else
			printf("\nBlack win\n");
		return (0);
	}
	if (infos->moves[move_idx].comment)
	{
		printf("\n");
		if (ft_strlen(infos->moves[move_idx].comment) == 1)
		{
			if (infos->moves[move_idx].comment[0] == '!')
				printf("Good move");
			else
				printf("Mistake");
		}
		else if (ft_strlen(infos->moves[move_idx].comment) == 2)
		{
			if (infos->moves[move_idx].comment[0] == '!'
				&& infos->moves[move_idx].comment[1] == '!')
				printf("Brilliant move");
			else if (infos->moves[move_idx].comment[0] == '!'
				&& infos->moves[move_idx].comment[1] == '?')
				printf("Interesting move");
			else if (infos->moves[move_idx].comment[0] == '?'
				&& infos->moves[move_idx].comment[1] == '?')
				printf("Blunder");
			else if (infos->moves[move_idx].comment[0] == '?'
				&& infos->moves[move_idx].comment[1] == '!')
				printf("Dubious move");
		}
		printf("\t");
	}
	else
		printf("\n");
	if (infos->moves[move_idx].eval)
		printf("\t%s", infos->moves[move_idx].eval);
	printf("\n\n");
	return (0);
}