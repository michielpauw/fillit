/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 12:25:35 by mpauw             #+#    #+#             */
/*   Updated: 2017/11/24 09:54:14 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	remove_piece(t_map **cur_map, size_t to_remove)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (*cur_map)->size)
	{
		j = 0;
		while (j < (*cur_map)->size)
		{
			if (((*cur_map)->map)[i][j] == (char)to_remove)
				(*cur_map)->map[i][j] = SEP;
			j++;
		}
		i++;
	}
}

void	print_cur_map(t_map **cur_map)
{
	size_t	i;
	size_t	k;

	i = 0;
	while (i < (*cur_map)->size)
	{
		k = 0;
		while (k < (*cur_map)->size)
		{
			ft_putchar(((*cur_map)->map)[i][k]);
			k++;
		}
		ft_putchar('\n');
		i++;
	}
}

t_map	*setup_map(size_t n)
{
	t_map	*map;
	size_t	i;

	i = 0;
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->n_pieces = n;
	map->min = ft_sqrt_cl(4 * n);
	map->max = map->min + 2;
	map->size = map->min;
	if (!(map->map = (char **)malloc(sizeof(char *) * (map->max + 1))))
		return (NULL);
	while (i < map->max)
	{
		if (!(map->map[i] = (char *)malloc(sizeof(char) * (map->max + 1))))
			return (NULL);
		ft_memset(map->map[i], SEP, map->max + 1);
		i++;
	}
	map->map[map->max] = NULL;
	return (map);
}
