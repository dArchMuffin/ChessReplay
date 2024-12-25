#include "header.h"
#include "stdio.h" //A virer quand j'aurai mis mon printf

int	print_piece(game_info *infos, int color)
{
	if (infos->moves[color].piece == PAWN) // Renommer color ?
		printf("pawn ");
	else if (infos->moves[color].piece == KNIGHT)
		printf("knight ");
	else if (infos->moves[color].piece == BISHOP)
		printf("bishop ");
	else if (infos->moves[color].piece == ROOK)
		printf("rook ");
	else if (infos->moves[color].piece == QUEEN)
		printf("queen ");
	else if (infos->moves[color].piece == KING)
		printf("king ");
}

void	print_piece_in(int board[8][8], char dest[2]) //To fix
{
    dest[1] = dest[1] - '0' - 1;
    dest[0] = dest[0] - 'a';
	if (board[dest[1]][dest[0]] == ' ')
		printf("no piece found ");
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
    else 
        printf("ERROR : [board[6][5] = %c | dest[1] = %d | dest[0] = %d]", board[6][5], dest[1] - '0' - 1, dest[0] - 'a');
}

// Renvoyer les coord de la case d'origine de la piece ?
int	*write_move(game_info *infos, int board[8][8], int color)
// Revoir le int color
{
	int i;

	if (infos->moves[color].is_mate == true) //Bug : n'affiche pas le move, ni w/b win
	{
		if (color % 2 == 0)
			printf("\nWhite win");
		else
			printf("\nBlack win");
		return (0);
	}
	// color of player's move
	if (color % 2 == 0)
		printf("\nWhite ");
	else
		printf("\nBlack ");
	// castle case
	if (infos->moves[color].type == SHORT_CASTLE)
		printf("short castle ");
	if (infos->moves[color].type == LONG_CASTLE)
		printf("long castle ");
	// piece moving
	print_piece(infos, color);
	// type of action
	if (infos->moves[color].type == NORMAL)
    {
		printf("moves to ");
        printf("%s", infos->moves[color].destination);
    }
	else if (infos->moves[color].type == CAPTURE)
	{
		printf("takes ");
		print_piece_in(board, infos->moves[color].destination);
		// la piece a la destination
		printf("in ");
		printf("%s", infos->moves[color].destination); //Bug ?
	}
	else
		printf("error in type\n");
	// if (infos->moves[color].destination[0])
	// 	printf("%s", infos->moves[color].destination);
	// else
	// 	printf("Error : no dest found\n");
	if (infos->moves[color].is_check == true)
		printf(". Check !");
	else
		printf(".");
	// Comment
	if (infos->moves[color].comment)
	{
		printf("\n");
		if (ft_strlen(infos->moves[color].comment) == 1)
		{
			if (infos->moves[color].comment[0] == '!')
				printf("Good move");
			else
				printf("Mistake");
		}
		else if (ft_strlen(infos->moves[color].comment) == 2)
		{
			if (infos->moves[color].comment[0] == '!'
				&& infos->moves[color].comment[1] == '!')
				printf("Brilliant move");
			else if (infos->moves[color].comment[0] == '!'
				&& infos->moves[color].comment[1] == '?')
				printf("Interesting move");
			else if (infos->moves[color].comment[0] == '?'
				&& infos->moves[color].comment[1] == '?')
				printf("Blunder");
			else if (infos->moves[color].comment[0] == '?'
				&& infos->moves[color].comment[1] == '!')
				printf("Dubious move");
		}
		printf("\t");
	}
	else
		printf("\n");
	// Evals
	if (infos->moves[color].eval)
		printf("\t%s", infos->moves[color].eval);
	printf("\n\n");
	return (0);
}