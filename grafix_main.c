/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:15:38 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/12 21:16:08 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafix.h"

void			read_until_strncmp(char **line, const char *str)
{
	if (!line || !str)
		return ;
	gnl(0, line);
	while (*line && ft_strncmp(*line, str, ft_strlen(str)) && \
			ft_strncmp(*line, "==", 2))
	{
		ft_strdel(line);
		gnl(0, line);
	}
}

static void		create_images(t_graf *s)
{
	char		*img;
	int			bits;
	int			size;
	int			endian;

	if (!s)
		free_and_exit(s);
	s->pl1_color = 0x5F;
	s->pl2_color = 0x5F0000;
	s->pl1_img = make_new_img(s, s->pl1_color);
	s->pl2_img = make_new_img(s, s->pl2_color);
	s->void_img = make_new_img(s, 0x5F5F5F);
	if (!(s->bg_img = mlx_new_image(s->mlx, s->win_width - 4, OFFSET - 2)))
		free_and_exit(s);
	bits = 1;
	size = s->img_width;
	endian = 1;
	if (!(img = mlx_get_data_addr(s->bg_img, &bits, &size, &endian)))
		free_and_exit(s);
	fill_img_color(img, (s->win_width - 4) * (OFFSET - 2), 0x2F2F2F);
	s->win = mlx_new_window(s->mlx, s->win_width, s->win_height, \
			"FILLER v1.0 by bsabre-c");
}

static void		start_calc(t_graf *s)
{
	char		**arr;

	if (!s || !(arr = start_read_input(s)))
		exit(1);
	s->mlx = mlx_init();
	s->arr_width = 0;
	while (arr[0][s->arr_width])
		s->arr_width++;
	s->arr_height = 0;
	while (arr[s->arr_height])
		s->arr_height++;
	if (s->arr_height < 15)
		s->win_height = 800 + OFFSET;
	else
		s->win_height = 1200 + OFFSET;
	if (s->arr_width < 15)
		s->win_width = 800;
	else
		s->win_width = 1200;
	s->img_width = s->win_width / s->arr_width - 2;
	s->img_height = (s->win_height - OFFSET) / s->arr_height - 2;
	s->win_height = (s->img_height + 2) * s->arr_height + 2 + OFFSET;
	s->win_width = (s->img_width + 2) * s->arr_width + 2;
	create_images(s);
}

int				main(void)
{
	t_graf		*s;

	if (!(s = (t_graf *)malloc(sizeof(t_graf) * 1)))
		return (1);
	bzero(s, sizeof(t_graf));
	start_calc(s);
	if (!s || !(s->pl1_img) || !(s->pl2_img) || !(s->bg_img) || !(s->void_img))
		free_and_exit(s);
	mlx_put_image_to_window(s->mlx, s->win, s->bg_img, 2, 2);
	mlx_string_put(s->mlx, s->win, 30, 5, s->pl1_color, s->pl1);
	mlx_string_put(s->mlx, s->win, 30, 25, s->pl2_color, s->pl2);
	paint_first_array(s, s->arr);
	mlx_loop_hook(s->mlx, loop_hook, s);
	mlx_key_hook(s->win, key_escape, s);
	mlx_mouse_hook(s->win, mouse_pause, s);
	mlx_loop(s->mlx);
	return (0);
}
