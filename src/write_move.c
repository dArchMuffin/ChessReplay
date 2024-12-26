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

void	print_piece_in(int board[8][8], char d[3]) //To fix
{
	char dest[3];

	dest[2] = '\0';
    dest[1] = d[1] - '0' - 1;
    dest[0] = d[0] - 'a';
	if (board[dest[1]][dest[0]] == ' ')
		printf("[no piece found] ");
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
	printf("in %c%c", dest[0] + 'a', dest[1] + 1 + '0');
    // else 
    //     printf("ERROR : [board[6][5] = %c | dest[1] = %d | dest[0] = %d]", board[6][5], dest[1] - '0' - 1, dest[0] - 'a');
}

// Renvoyer les coord de la case d'origine de la piece ?
int	*write_move(game_info *infos, int board[8][8], int move_idx)
// Revoir le int move_idx
{
	int i;

	// move_idx of player's move ->fct ?
	if (move_idx % 2 == 0)
		printf("\nWhite ");
	else
		printf("\nBlack ");
	// castle case
	if (infos->moves[move_idx].type == SHORT_CASTLE)
		printf("short castle ");
	if (infos->moves[move_idx].type == LONG_CASTLE)
		printf("long castle ");
	// piece to move
	print_piece(infos, move_idx);
	// type of action
	if (infos->moves[move_idx].type == NORMAL)
		printf("moves to %s", infos->moves[move_idx].destination);
	else if (infos->moves[move_idx].type == CAPTURE)
	{
		printf("takes ");
		print_piece_in(board, infos->moves[move_idx].destination);
	}
	else
		printf("error in type\n");
	//check / comment / evals
	if (infos->moves[move_idx].is_check == true)
		printf(". Check !");
	else if (infos->moves[move_idx].is_mate == true)
		printf(". Checkmate !");
	else
		printf(".");
	if (infos->moves[move_idx].is_mate == true)
	{
		if (move_idx % 2 == 0)
			printf("\nWhite win\n");
		else
			printf("\nBlack win\n");
		return (0);
	}
	printf("\t #%d : [%s]", move_idx, infos->moves[move_idx].pgn);
	// Comment ->fct 
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
	// Evals
	if (infos->moves[move_idx].eval)
		printf("\t%s", infos->moves[move_idx].eval);
	printf("\n\n");
	return (0);
}