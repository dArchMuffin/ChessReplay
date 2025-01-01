#include "header.h"
#include <stdio.h> //libft printf
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int	main(int ac, char **av)
{
	int			board[8][8];
	game_info	game_info;
	int			game_number;
	int			e;
	int			move_idx;
	int			turn;
	int			timer;

	timer = 0;
	if (ac > 1) // chess 5 : replay game nb 5
		timer = atoi(av[1]); // libft atoi
	if (ac > 2) //./chess 5 1 : 1 sec timer replaying
		game_number = atoi(av[2]);
	else
	{
		srand(time(NULL));
		game_number = rand() % 355733;
		printf("game #%d\n", game_number);
	}
	e = read_game(game_number, &game_info);
	if (e < 0)
	{
		printf("Error while parsing game\n");
		return (-1);
	}
	init_board(board);
	print_board(board, &game_info);
	turn = 1;
	move_idx = 0;
	while (1)
	{
		if (turn > game_info.nb_moves / 2)
			break ;
		printf("\n                                     +----------+");
		printf("\n====================================<| Turn #%d |>====================================",
			turn);
		printf("\n                                     +----------+\n");
		turn++;
		if (endgame_check(&game_info, move_idx) == 1)
			break ;
		write_move(&game_info, board, move_idx);
		update_board(&game_info, board, move_idx);
		print_board(board, &game_info);
		if (game_info.moves[move_idx].is_mate == true 
		|| game_info.moves[move_idx].is_resign == true
		|| game_info.moves[move_idx].is_draw == true
		|| game_info.moves[move_idx].is_time_out == true)
			break ;
		sleep(timer);
		move_idx++;
		if (endgame_check(&game_info, move_idx) == 1)
			break ;
		write_move(&game_info, board, move_idx);
			if (game_info.moves[move_idx].is_time_out == true)
			break ;
		update_board(&game_info, board, move_idx);
		print_board(board, &game_info);
		sleep(timer);
		move_idx++;
	}
	free_game_info(&game_info);
	return (0);
}
