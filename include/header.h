#ifndef CHESS
# define CHESS

# include <stdbool.h>
# include <unistd.h>

typedef enum
{
	NONE,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
}			piece_type;

typedef enum
{
	NORMAL,
	SHORT_CASTLE,
	LONG_CASTLE,
	CAPTURE
}			move_type;

typedef struct
{
	piece_type piece; // quelle piece ?
	move_type type;   // x ou deplacement ou speciaux
	char	*eval;
	char	destination[2];
	char	col_hint;
	char	row_hint;
	bool color; // false == white / true == black
	bool	is_check;
	bool	is_mate;
	void	*next;
}			move;

typedef struct
{
	char	**headers;
	int		nb_headers;
	move	*moves;
	int		nb_moves;
}			game_info;

// libft
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
// Chess
int			read_game(int game_number, game_info *infos);
void		init_board(int board[8][8]);
void		print_board(int board[8][8], game_info *infos);
void	free_game_info(game_info *game_info);

#endif