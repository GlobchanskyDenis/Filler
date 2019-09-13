/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:44:47 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/12 21:00:09 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafix.h"

int		key_escape(int key, t_graf *s)
{
	if (key == ESCAPE)
		free_and_exit(s);
	return (0);
}

int		mouse_pause(int param, int x, int y, t_graf *s)
{
	if (!s || (!param && !x && !y))
		return (-1);
	if (s->is_pause == 0)
		s->is_pause = 1;
	else
		s->is_pause = 0;
	return (0);
}

int		loop_hook(t_graf *s)
{
	if (!s)
		return (-1);
	if (s->is_end == 1)
		return (0);
	if (s->is_pause)
		mlx_string_put(s->mlx, s->win, 600, 15, 0x5F00, "PAUSE");
	else
	{
		read_input(s);
		paint_new_array(s, s->arr, s->old_arr);
		mlx_put_image_to_window(s->mlx, s->win, s->bg_img, 2, 2);
		mlx_string_put(s->mlx, s->win, 30, 5, s->pl1_color, s->pl1);
		mlx_string_put(s->mlx, s->win, 30, 25, s->pl2_color, s->pl2);
	}
	return (0);
}
