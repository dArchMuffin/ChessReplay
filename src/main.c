#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int			board[8][8];
	game_info	game_info;
	int			game_number;
	int			e;
	int			i;
	bool		gameover;
	int			turn;

	gameover = true;
	if (ac != 1)
		game_number = atoi(av[1]); // coder atoi
	else
		game_number = 0;
	e = read_game(game_number, &game_info);
	if (e < 0)
	{
		printf("Error while parsing game\n");
		return (-1);
	}
	init_board(board);
	print_board(board, &game_info);
	turn = 1;
	i = 0;
	while (1) // pas sûr ...
	{
		if (turn > game_info.nb_moves / 2)
			break ;
		printf("\n                                     +----------+");
		printf("\n====================================<| Turn #%d |>====================================",
			turn);
		printf("\n                                     +----------+\n");
		turn++;
		write_move(&game_info, board, i);
		// update board : update board with last move
		print_board(board, &game_info);
		sleep(1);
		i++;
		write_move(&game_info, board, i);
		// update board
		print_board(board, &game_info);
		sleep(1);
		i++;
	}
	free_game_info(&game_info);
	return (0);
}
