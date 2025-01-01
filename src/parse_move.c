#include "header.h"


void	set_promotion(char *game, int i, move *m)
{
	m->is_promotion = false;
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == '=')
		{
			m->is_promotion = true;
			if (game[i + 1] == 'R')
				m->promoted = ROOK;
			else if (game[i + 1] == 'N')
				m->promoted = KNIGHT;
			else if (game[i + 1] == 'B')
				m->promoted = BISHOP;
			else if (game[i + 1] == 'Q')
				m->promoted = QUEEN;
		}
		i++;
	}
}

void	set_resign(char *game, int i, move *m)
{
	if (game[i] == '1')
	{
		if (game[i + 1] == '/')
			m->is_draw = true;
		else if (game[i + 1] == '-')
			m->is_resign = true;
		while (game[i] && game[i] != ' ')
			i++;
	}
	else if (game[i] == '0')
	{
		m->is_resign = true;
		while (game[i] && game[i] != ' ')
			i++;
	}
	else
	{
		m->is_draw = false;
		m->is_resign = false;
	}
}

void	set_caslte(char *game, int i, move *m)
{
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == 'O')
		{
			if (game[i + 3] == '-')
			{
				m->type = LONG_CASTLE;
				break ;
			}
			else if (game[i + 3] == ' ')
			{
				m->type = SHORT_CASTLE;
				break ;
			}
		}
		else
			m->type = NORMAL;
		i++;
	}
}

void	set_check(char *game, int i, move *m)
{
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == '+')
		{
			m->is_check = true;
			break ;
		}
		i++;
	}
	if (game[i] == ' ')
		m->is_check = false;
}

void	set_capture(char *game, int i, move *m)
{
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == 'x')
		{
			m->type = CAPTURE;
			break ;
		}
		i++;
	}
	if (game[i] == ' ' && m->type != LONG_CASTLE && m->type != SHORT_CASTLE)
		m->type = NORMAL;
}

void	set_checkmate(char *game, int i, move *m)
{
	while (game[i] && game[i] != ' ')
	{
		if (game[i] == '#')
		{
			m->is_mate = true;
			break ;
		}
		i++;
	}
	if (game[i] == ' ')
		m->is_mate = false;
}

void	get_comment(char *game, int i, int start, int len, move *m)
{
	int	j;

	j = 0;
	while (game[i] && i - start < len && game[i] != ' ')
	{
		if (game[i] == '!' || game[i] == '?')
		{
			m->comment[j] = game[i];
			j++;
		}
		i++;
	}
	m->comment[j] = '\0';
}

void	set_piece(char *game, int i, move *m)
{
	if (game[i] && game[i] >= 'a' && game[i] <= 'h')
		m->piece = PAWN;
	else
	{
		if (game[i] == 'N')
			m->piece = KNIGHT;
		else if (game[i] == 'B')
			m->piece = BISHOP;
		else if (game[i] == 'R')
			m->piece = ROOK;
		else if (game[i] == 'Q')
			m->piece = QUEEN;
		else if (game[i] == 'K')
			m->piece = KING;
		else
			m->piece = NONE;
		i++;
	}
}

void	set_hints(char *game, int i, move *m)
{
	m->col_hint = '\0';
	m->row_hint = '\0';
	if (m->piece == ROOK || m->piece == BISHOP || m->piece == KNIGHT
		|| m->piece == QUEEN)
	{
		while (game[i] && game[i] != ' ')
			i++;
		while (ft_isdigit(game[i]) == 0)
			i--;
		i -= 2;
		if (game[i] == 'N' || game[i] == 'R' || game[i] == 'B'
			|| game[i] == 'Q')
			return ;
		else if (game[i] == 'x')
		{
			if (ft_isdigit(game[i - 1]) == 1)
				m->row_hint = game[i - 1];
			else if (ft_islowercase(game[i - 1]) == 1)
				m->col_hint = game[i - 1];
		}
		else if (ft_isdigit(game[i]) == 1)
		{
			m->row_hint = game[i];
			if (ft_islowercase(game[i - 1]) == 1)
				m->col_hint = game[i - 1];
		}
		else if (ft_islowercase(game[i]) == 1)
			m->col_hint = game[i];
	}
}

void	get_destination(char *game, int i, move *m)
{
	m->destination[0] = '\0';
	m->destination[1] = '\0';
	m->destination[2] = '\0';
	if (m->type == NORMAL || m->type == CAPTURE)
	{
		while (game[i] != ' ' && game[i])
			i++;
		while (ft_isdigit(game[i]) == 0)
			i--;
		m->destination[0] = game[i - 1];
		m->destination[1] = game[i];
		m->destination[2] = '\0';
	}
}

void	get_eval(char *game, int i, int start, move *m)
{
	if (game[i + 1] == '{')
	{
		while (game[i] && game[i] != '%')
			i++;
		start = i + 1;
		while (game[i] && game[i] != ']')
			i++;
		m->eval = ft_substr(game, start, i - start);
	}
	else
		m->eval = NULL;
}

move	parse_moves(char *game, int i)
{
	move	m;
	int		start;
	int		j;
	int		len;

	start = i;
	m.is_time_out = false;
	m.promoted = NONE;
	while (game[i] && game[i] != ' ')
		i++;
	m.pgn = ft_substr(game, start, i - start);
	len = ft_strlen(m.pgn);
	i = start;
	set_promotion(game, i, &m);
	set_resign(game, i, &m);
	set_caslte(game, i, &m);
	set_check(game, i, &m);
	set_capture(game, i, &m);
	set_checkmate(game, i, &m);
	get_comment(game, i, start, len, &m);
	set_piece(game, i, &m);
	set_hints(game, i, &m);
	get_destination(game, i, &m);
	while (game[i] && game[i] != ' ')
		i++;
	get_eval(game, i, start, &m);
	return (m);
}