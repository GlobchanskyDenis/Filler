/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:15:37 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/13 15:06:51 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_positions_fill_map(t_data *s)
{
	if (!s)
		return ;
	print_array(s->map, s->map_size, s, "map");
	print_array(s->fig, s->fig_size, s, "figure");
	fprint_fd(s->fd, "Initialize positions\n");
	(s->cur).x = 0;
	(s->cur).y = 0;
	(s->best).x = 0;
	(s->best).y = 0;
	s->cur_count = 0;
	s->best_count = 1000000;
	fill_map_by_ranks(s->map, 1, s);
	fprint_fd(s->fd, "Successfull filling map\nMake algorithm\n");
}

static void	make_current_position_best(t_pos o, t_data *s)
{
	if (!s)
		return ;
	s->best_count = s->cur_count;
	(s->best).x = (s->cur).x - o.x;
	(s->best).y = (s->cur).y - o.y;
	fprint_fd(s->fd, "new best place was found : %d %d\n", (s->best).x, \
			(s->best).y);
}

int			algorithm(t_data *s)
{
	t_pos	o;
	int		ret;

	if (!s || !(s->map) || !(s->fig))
		return (0);
	o = init_offset(s->fig, s);
	init_positions_fill_map(s);
	ret = 0;
	while ((s->map)[(s->cur).x])
	{
		(s->cur).y = 0;
		while ((s->map)[(s->cur).x][(s->cur).y])
		{
			fprint_fd(s->fd, "%d %d\n", (s->cur).x, (s->cur).y);
			if (is_can_put_figure(alloc_cpy_fig(s->fig), s->cur, o, s) && \
					(s->cur_count < s->best_count))
			{
				ret = 1;
				make_current_position_best(o, s);
			}
			(s->cur).y++;
		}
		(s->cur).x++;
	}
	return (ret);
}
