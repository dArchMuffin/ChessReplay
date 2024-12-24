#ifndef CHESS
# define CHESS

# include <stdbool.h>
# include <unistd.h>

typedef struct
{
	char	**headers;
	int		nb_headers;
	char	*moves;
	int		nb_moves;
}			game_info;

typedef struct
{
	char destination[2];
	bool is_check;
	bool is_mate;
	char col_hint;
	char row_hint;
} move;

int			read_game(int game_number, game_info *infos);
void		init_board(int board[8][8]);
void		print_board(int board[8][8], game_info *infos);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif