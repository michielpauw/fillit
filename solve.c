/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 08:34:55 by mpauw             #+#    #+#             */
/*   Updated: 2017/11/24 17:47:43 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		fit_piece(t_refined *cur_piece, t_map **cur_map,
		t_point *cur_p)
{
	int	i;
	int	j;

	i = cur_piece->height - 1;
	while (i >= 0)
	{
		j = cur_piece->width - 1;
		while (j >= 0)
		{
			if ((cur_piece->array)[i][j] && (*cur_map)->map[i +
					cur_p->y][j + cur_p->x] == SEP)
				(*cur_map)->map[i + cur_p->y][j
					+ cur_p->x] = (cur_piece->array)[i][j];
			j--;
		}
		i--;
	}
}

static int		get_is_fit(t_map **cur_map, t_point *cur_p,
		t_refined *cur_piece)
{
	int	i;
	int	j;

	i = cur_piece->height - 1;
	j = cur_piece->width - 1;
	if ((size_t)(cur_p->y + i) >= (*cur_map)->size)
		return (-1);
	if ((size_t)(cur_p->x + j) >= (*cur_map)->size)
		return (0);
	while (i >= 0)
	{
		j = cur_piece->width - 1;
		while (j >= 0)
		{
			if ((cur_piece->array)[i][j] && (*cur_map)->map[i + cur_p->y]
					[j + cur_p->x] != SEP)
				return (0);
			j--;
		}
		i--;
	}
	return (1);
}

static int		get_free(t_map **cur_map, t_point **cur_p,
		t_refined *cur_piece)
{
	int	is_fit;
	int	first;

	first = 1;
	while (first || !(is_fit = get_is_fit(cur_map, *cur_p, cur_piece)))
	{
		first = 0;
		(*cur_p)->x = ((*cur_p)->x + 1) % (*cur_map)->size;
		if (!(*cur_p)->x)
			(*cur_p)->y++;
		if ((size_t)((*cur_p)->y) > (*cur_map)->size)
			return (0);
	}
	if (is_fit == -1)
		return (0);
	return (1);
}

static void		update_point(t_point **cur_p, int x, int y)
{
	(*cur_p)->x = x;
	(*cur_p)->y = y;
}

int				solve(t_refined **pieces, t_map **cur_map,
		t_point *cur_p, size_t i)
{
	size_t	j;
	size_t	x;
	size_t	y;

	update_point(&cur_p, -1, -1);
	if (i == (*cur_map)->n_pieces)
		return (1);
	j = -1;
	while (get_free(cur_map, &cur_p, pieces[i]))
	{
		fit_piece(pieces[i], cur_map, cur_p);
		x = cur_p->x;
		y = cur_p->y;
		if ((solve(pieces, cur_map, cur_p, i + 1)))
			return (1);
		update_point(&cur_p, x, y);
		remove_piece(cur_map, (pieces[i])->c);
	}
	return (0);
}
