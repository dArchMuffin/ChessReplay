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
  // int i = 0;
  // while(i < game_info.nb_headers)
  // {
  //   printf("%s", game_info.headers[i]);
  //   i++;
  // }
  // printf("%s", game_info.moves);
  // get_game_info(buf, buf_len, game_info *gameinfo)
  // get_pgn()
	// On initiliase le board
	return (0);
}
