/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:19:52 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/12 21:12:22 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafix.h"

void		draw_score(t_graf *s)
{
	int		offset;
	char	*tmp;

	if (!s || !(s->line) || !(s->pl1) || !(s->pl2) || !(s->mlx) || !(s->win))
		free_and_exit(s);
	s->pl1_score = ft_atoi(&((s->line)[9]));
	ft_strdel(&(s->line));
	gnl(0, &(s->line));
	s->pl2_score = ft_atoi(&((s->line)[9]));
	ft_strdel(&(s->line));
	gnl(0, &(s->line));
	ft_strdel(&(s->line));
	offset = ft_max_i((int)ft_strlen(s->pl1), (int)ft_strlen(s->pl2)) + 2;
	offset = offset * 10;
	tmp = ft_itoa(s->pl1_score);
	mlx_string_put(s->mlx, s->win, 30 + offset, 5, s->pl1_color, tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(s->pl2_score);
	mlx_string_put(s->mlx, s->win, 30 + offset, 25, s->pl2_color, tmp);
	ft_strdel(&tmp);
	s->is_pause = 1;
	s->is_end = 1;
	mlx_loop(s->mlx);
}

static char	**read_map(t_graf *s, char **arr, int size)
{
	int		i;
	int		j;

	if (!s || !arr)
		free_and_exit(s);
	i = 0;
	while (i < size)
	{
		gnl(0, &(s->line));
		arr[i] = ft_strdup(&((s->line)[4]));
		ft_strdel(&(s->line));
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == 'x')
				arr[i][j] = 'X';
			else if (arr[i][j] == 'o')
				arr[i][j] = 'O';
			j++;
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void		read_input(t_graf *s)
{
	int		size;

	if (!s)
		free_and_exit(s);
	if (s->old_arr)
		delete_array_(&(s->old_arr));
	s->old_arr = s->arr;
	s->arr = NULL;
	read_until_strncmp(&(s->line), "Plateau ");
	if (!(s->line) || !strncmp(s->line, "==", 2))
		draw_score(s);
	size = 0;
	size = atoi(&((s->line)[7]));
	ft_strdel(&(s->line));
	gnl(0, &(s->line));
	ft_strdel(&(s->line));
	if (!(s->arr = (char **)malloc(sizeof(char *) * (size + 1))))
		free_and_exit(s);
	s->arr = read_map(s, s->arr, size);
}

char		**start_read_input(t_graf *s)
{
	int		i;

	if (!s)
		exit(1);
	read_until_strncmp(&(s->line), "$$$ exec p1 : [");
	i = 0;
	while (s->line && (s->line)[i] && (s->line)[i] != ']')
		i++;
	if (i > 15)
		s->pl1 = ft_strsub(s->line, 15, i - 15);
	ft_strdel(&(s->line));
	read_until_strncmp(&(s->line), "$$$ exec p2 : [");
	i = 15;
	while (s->line && (s->line)[i] && (s->line)[i] != ']')
		i++;
	if (i > 15)
		s->pl2 = ft_strsub(s->line, 15, i - 15);
	ft_strdel(&(s->line));
	read_input(s);
	return (s->arr);
}
