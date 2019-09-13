/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:37:40 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/12 21:08:52 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafix.h"

void		fill_img_color(char *img, size_t count, int color)
{
	char		col1;
	char		col2;
	char		col3;

	if (!img)
		return ;
	col1 = (char)(color & 0xFF);
	col2 = (char)((color & (0xFF << 8)) >> 8);
	col3 = (char)((color & (0xFF << 16)) >> 16);
	while (count--)
	{
		*img = col1;
		img++;
		*img = col2;
		img++;
		*img = col3;
		img++;
		*img = 0;
		img++;
	}
}

void		*make_new_img(t_graf *s, int color)
{
	void		*dst;
	char		*img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	if (!s)
		return (NULL);
	if (!(dst = mlx_new_image(s->mlx, s->img_width, s->img_height)))
		return (NULL);
	bits_per_pixel = 1;
	size_line = s->img_width;
	endian = 1;
	if (!(img = mlx_get_data_addr(dst, &bits_per_pixel, &size_line, &endian)))
		return (NULL);
	fill_img_color(img, s->img_width * s->img_height, color);
	return (dst);
}

static int	put_image_to_window(t_graf *s, void *img, int i, int j)
{
	if (!s || !img)
		return (0);
	return (mlx_put_image_to_window(s->mlx, s->win, img, 2 + j * \
				(s->img_width + 2), 2 + OFFSET + i * (s->img_height + 2)));
}

void		paint_first_array(t_graf *s, char **arr)
{
	int			i;
	int			j;

	if (!s || !arr || !(*arr))
		return ;
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '.')
				put_image_to_window(s, s->void_img, i, j);
			else if (arr[i][j] == 'O')
				put_image_to_window(s, s->pl1_img, i, j);
			else if (arr[i][j] == 'X')
				put_image_to_window(s, s->pl2_img, i, j);
			j++;
		}
		i++;
	}
}

void		paint_new_array(t_graf *s, char **arr, char **old_arr)
{
	int			i;
	int			j;

	if (!s || !arr || !(*arr) || !old_arr || !(old_arr))
		return ;
	i = 0;
	while (arr[i] && old_arr[i])
	{
		j = 0;
		while (arr[i][j] && old_arr[i][j])
		{
			if (arr[i][j] != old_arr[i][j])
			{
				if (arr[i][j] == 'O')
					put_image_to_window(s, s->pl1_img, i, j);
				else if (arr[i][j] == 'X')
					put_image_to_window(s, s->pl2_img, i, j);
			}
			j++;
		}
		i++;
	}
}
