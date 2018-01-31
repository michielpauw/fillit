/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 07:51:08 by dolivier          #+#    #+#             */
/*   Updated: 2017/11/27 10:43:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int			*get_dimensions(t_piece *piece)
{
	int	i;
	int	*dim;

	if (!(dim = (int *)malloc(sizeof(int) * 4)))
		ft_error();
	i = 3;
	while (i >= 0)
		(dim)[i--] = -1;
	i++;
	while ((piece->str)[i])
	{
		if ((piece->str)[i] == '#')
		{
			if ((dim)[0] == -1)
				(dim)[0] = i / 5;
			if ((dim)[1] == -1 || (dim)[1] > i % 5)
				(dim)[1] = i % 5;
			if ((dim)[2] == -1 || (dim)[2] < i % 5)
				(dim)[2] = i % 5;
			if ((dim)[3] == -1 || (dim)[3] < i / 5)
				(dim)[3] = i / 5;
		}
		i++;
	}
	return (dim);
}

static t_refined	*ft_piecetorefined(t_piece *piece, int index)
{
	int				i;
	int				j;
	int				*dim;
	t_refined		*refined;

	dim = get_dimensions(piece);
	if (!(refined = (t_refined *)malloc(sizeof(t_refined))))
		return (NULL);
	i = dim[0] - 1;
	while (++i < dim[3] + 1)
	{
		j = dim[1] - 1;
		while (++j < dim[2] + 1)
		{
			if (piece->str[5 * i + j] == '#')
				refined->array[i - dim[0]][j - dim[1]] = 'A' + index;
		}
		refined->array[i - dim[0]][j - dim[1]] = 0;
	}
	refined->c = 'A' + index;
	refined->array[i - dim[0]][0] = 0;
	refined->height = dim[3] - dim[0] + 1;
	refined->width = dim[2] - dim[1] + 1;
	return (refined);
}

t_refined			**ft_createpieces(char *str)
{
	int			amount;
	int			j;
	t_piece		*piece;
	t_piece		*tmp;
	t_refined	**piece_arr;

	j = 0;
	amount = ft_check_validity(str);
	ft_neighbor(str);
	piece_arr = (t_refined **)malloc(sizeof(t_refined *) * 27);
	if (!(piece = (t_piece *)malloc(sizeof(t_piece))) || !(piece_arr))
		return (NULL);
	tmp = piece;
	while (amount-- > 0)
	{
		tmp->str = ft_strncpy(ft_strnew(20), &str[j], 20);
		piece_arr[j / 21] = ft_piecetorefined(tmp, j / 21);
		j = j + 21;
		if ((tmp->next = (t_piece *)malloc(sizeof(t_piece))) == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	piece_arr[j / 21] = NULL;
	return (piece_arr);
}

char				*ft_reader(char *file)
{
	int		fd;
	int		read_stat;
	int		i;
	char	tmp[545];
	char	buffer[1];

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error();
	while ((read_stat = read(fd, buffer, 1)))
	{
		tmp[i++] = buffer[0];
		if (i > 545)
			ft_error();
	}
	tmp[i] = '\0';
	if (close(fd) != 0)
		ft_error();
	return (ft_strdup(tmp));
}
