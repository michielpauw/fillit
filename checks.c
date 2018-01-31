/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:51:22 by dolivier          #+#    #+#             */
/*   Updated: 2017/11/27 08:56:45 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_count(char *str, int *i, int *j)
{
	if (str[*i] == '#')
	{
		if (str[*i + 1] == '#')
			*j = *j + 1;
		if (str[*i - 1] == '#')
			*j = *j + 1;
		if (str[*i + 5] == '#')
			*j = *j + 1;
		if (str[*i - 5] == '#')
			*j = *j + 1;
	}
}

void		ft_neighbor(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '.')
			i++;
		ft_count(str, &i, &j);
		if ((str[i] == '\n' && (str[i + 1] == '\n' ||
						str[i + 1] == '\0')) && j < 6)
			ft_error();
		if (((str[i] == '\n' && str[i + 1] == '\n') || i <= 18) && j >= 6)
		{
			j = 0;
			i = -1;
			str = str + 21;
		}
		i++;
	}
}

static void	ft_check_line(char *input, int *char_on_line, int *eol)
{
	if (*(input - 1) != '\n')
	{
		if (*char_on_line != 5)
			ft_error();
		if (!((*eol + 1) % 5))
			ft_error();
	}
	*char_on_line = 0;
	(*eol)++;
}

int			ft_check_validity(char *input)
{
	int		dot;
	int		hash;
	int		eol;
	int		char_on_line;

	dot = 0;
	hash = 0;
	eol = 0;
	char_on_line = 0;
	while (*input != '\0')
	{
		char_on_line++;
		if (*input == '.')
			dot++;
		else if (*input == '#')
			hash++;
		else if (*input == '\n')
			ft_check_line(input, &char_on_line, &eol);
		else
			ft_error();
		input++;
	}
	if (dot % 12 != 0 || hash % 4 != 0 || hash * 3 != dot || eol % 5 != 4)
		ft_error();
	return (hash / 4);
}
