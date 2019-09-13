/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_figure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 11:58:27 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/13 15:04:21 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		**alloc_cpy_fig(char **fig)
{
	char	**dst;
	int		i;
	int		size;

	if (!fig || !(*fig))
		return (NULL);
	i = 0;
	size = 0;
	while (fig[size])
		size++;
	if (!(dst = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		dst[i] = ft_strdup(fig[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

static int	is_all_dots(char **fig, t_data *s)
{
	int		i;
	int		j;

	if (!s || !fig)
		return (0);
	fprint_fd(s->fd, "Is_all_dots - placed well?\t");
	i = 0;
	while (fig[i])
	{
		j = 0;
		while (fig[i][j])
		{
			if (fig[i][j] != '.')
			{
				fprint_fd(s->fd, "figure is not placed well %d %d\n", i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	fprint_fd(s->fd, "figure placed well\n");
	return (1);
}

t_pos		init_offset(char **fig, t_data *s)
{
	t_pos	offset;
	t_pos	i;

	offset.x = 0;
	offset.y = 0;
	if (!fig || !s)
		return (offset);
	while (fig[offset.x] && fig[offset.x][offset.y] != '*')
	{
		while (fig[offset.x][offset.y] == '.')
			offset.y++;
		if (fig[offset.x][offset.y] != '*' && ++(offset.x))
			offset.y = 0;
	}
	i.x = offset.x;
	i.y = 0;
	while (fig[i.x])
	{
		i.y = 0;
		while (i.y < offset.y && fig[i.x][i.y])
			(fig[i.x][i.y] == '*') ? (offset.y = i.y) : (i.y++);
		i.x++;
	}
	fprint_fd(s->fd, "Offset was found: %d %d\n", offset.x, offset.y);
	return (offset);
}

static void	check_dot(char map_symb, char *fig_symb, t_data *s)
{
	if (!fig_symb || !fig_symb || !s)
		return ;
	if ((map_symb == (s->id).pl || map_symb == (s->id).pl + 32) && \
			*fig_symb != '.')
		s->flag = -1;
	else if (map_symb <= '.' || *fig_symb == '.' || s->flag == 1)
	{
		if (map_symb > '.' && *fig_symb != '.')
			s->flag = 0;
		else
			s->cur_count += (int)map_symb;
		*fig_symb = '.';
	}
	else
		s->flag = -1;
}

int			is_can_put_figure(char **fig, t_pos m, t_pos o, t_data *s)
{
	t_pos		f;

	if (!fig || !s || !(s->map))
		return (0);
	f.x = 0;
	s->flag = 1;
	s->cur_count = 0;
	while (fig[o.x + f.x] && (s->map)[m.x + f.x])
	{
		f.y = 0;
		while (fig[o.x + f.x][o.y + f.y] && (s->map)[m.x + f.x][m.y + f.y])
		{
			check_dot((s->map)[m.x + f.x][m.y + f.y], \
					&(fig[o.x + f.x][o.y + f.y]), s);
			f.y++;
		}
		f.x++;
	}
	if (s->flag == 0 && is_all_dots(fig, s))
	{
		delete_array(&fig, s->fig_size, s);
		return (1);
	}
	delete_array(&fig, s->fig_size, s);
	return (0);
}
