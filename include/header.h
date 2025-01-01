#ifndef CHESSREPLAY
# define CHESSREPLAY

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
}				piece_type;

typedef enum
{
	NORMAL,
	SHORT_CASTLE,
	LONG_CASTLE,
	CAPTURE
}				move_type;

typedef enum
{
	WHITE_WIN,
	BLACK_WIN,
	DRAW,
	PNEDING,
}				result;

typedef struct
{
	piece_type piece;
	move_type type;
	result		res;
	char		*pgn;
	char		*eval;
	char		comment[3];
	char		destination[3];
	char		col_hint;
	char		row_hint;
	bool		is_check;
	bool		is_mate;
	bool		is_draw;
	bool		is_resign;
	bool		is_time_out;
	bool		is_promotion;

	piece_type	promoted;
}				move;

typedef struct
{
	char		**headers;
	int			nb_headers;
	move		*moves;
	int			nb_moves;
}				game_info;

// libft
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_islowercase(int c);

// Chess
// Parsing
int				read_game(int game_number, game_info *infos);
void			free_game_info(game_info *game_info);
move			parse_moves(char *game, int i);

// Board
void			init_board(int board[8][8]);
void			print_board(int board[8][8], game_info *infos);
// write_move
int				*write_move(game_info *infos, int board[8][8], int move_idx);
// update_board
void			update_board(game_info *infos, int board[8][8], int move_idx);
void			no_hint_case(game_info *infos, int board[8][8], int move_idx);
void			col_hint_case(game_info *infos, int board[8][8], int move_idx);
void			row_hint_case(game_info *infos, int board[8][8], int move_idx);
// cleaners
void			clean_origin(game_info *infos, int board[8][8], int move_idx);
int				clean_knight(char p, char start_y, char start_x,
					int board[8][8], int move_idx);
int				clean_piece_in_lines(char p, char start_y, char start_x,
					int board[8][8], int move_idx);
int	clean_piece_in_diags(char p, char start_y, char start_x, int board[8][8],
							int move_idx);
int				clean_king(char p, char start_y, char start_x, int board[8][8],
					int move_idx);

int				endgame_check(game_info *infos, int move_idx);

#endif