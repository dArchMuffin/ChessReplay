#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	board[8][8];
  game_info game_info;
  int game_number;
  int e;
  int i;

  if (ac != 1)
    game_number = atoi(av[1]);
  else 
    game_number = 0;
  e = read_game(game_number, &game_info);
  if (e < 0) {
    printf("Error while parsing game\n");
    return (-1);
  }
	init_board(board);
	print_board(board, &game_info);
  free_game_info(&game_info);
	return (0);
}
