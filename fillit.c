/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:32:25 by dolivier          #+#    #+#             */
/*   Updated: 2017/11/27 10:45:13 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_error(void)
{
	write(1, "error\n", 6);
	exit(0);
}

void		ft_print_usage(void)
{
	ft_putstr("usage: ./fillit source_file\n");
}

int			main(int argc, char **argv)
{
	t_refined		**pieces;
	size_t			i;
	size_t			k;
	t_map			*cur_map;
	t_point			*cur_point;

	if (argc != 2)
	{
		ft_print_usage();
		return (0);
	}
	pieces = ft_createpieces(ft_reader(argv[1]));
	k = 0;
	while (*(pieces + k))
		k++;
	cur_map = setup_map(k);
	i = 0;
	cur_point = (t_point *)malloc(sizeof(t_point));
	cur_point->x = -1;
	cur_point->y = -1;
	while (!(solve(pieces, &cur_map, cur_point, i)))
		(cur_map->size)++;
	print_cur_map(&cur_map);
	return (0);
}
