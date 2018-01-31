/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:57:51 by dolivier          #+#    #+#             */
/*   Updated: 2017/11/24 17:58:27 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLIT_H
# define FT_FILLIT_H
# define SEP '.'

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft.h"

typedef struct	s_piece
{
	char				*str;
	struct s_piece		*next;
}				t_piece;

typedef struct	s_refined
{
	char		array[4][4];
	size_t		height;
	size_t		width;
	char		c;
}				t_refined;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_map
{
	char		**map;
	size_t		n_pieces;
	size_t		size;
	size_t		min;
	size_t		max;
}				t_map;

void			ft_error(void);
int				ft_check_validity(char *input);
void			ft_neighbor(char *str);
t_refined		**ft_createpieces(char *str);
char			*ft_reader(char *file);
int				main(int argc, char **argv);
t_map			*setup_map(size_t n);
int				solve(t_refined **pieces, t_map **cur_map,
		t_point *cur_point, size_t i);
void			remove_piece(t_map **cur_map, size_t to_remove);
void			print_cur_map(t_map **cur_map);

#endif
