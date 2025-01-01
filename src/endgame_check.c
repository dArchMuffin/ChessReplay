#include <stdio.h>
#include "header.h"

int endgame_check(game_info *infos, int move_idx)
{
    if (move_idx == infos->nb_moves - 1
    && infos->moves[move_idx].is_mate == 0
    && infos->moves[move_idx].is_draw == 0
    && infos->moves[move_idx].is_resign == 0
    && infos->moves[move_idx].is_time_out == 0) 
    {
        if (infos->headers[4][9] == '0')
            printf("\nWhite resign. Black win.\n\n");
        else if (infos->headers[4][10] == '/')
            printf("\nDraw.\n");
        else if (infos->headers[4][11] == '0')
            printf("\nBlack resign. White win.\n\n");
        return (1);
    }
    return (0);
}