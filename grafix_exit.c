/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:47:12 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/12 18:36:37 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafix.h"

void	delete_array_(char ***arr)
{
	int		i;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i++] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void	free_and_exit(t_graf *s)
{
	if (!s)
		exit(1);
	if (s->pl1)
		ft_strdel(&(s->pl1));
	if (s->pl2)
		ft_strdel(&(s->pl2));
	if (s->bg_img)
		mlx_destroy_image(s->mlx, s->bg_img);
	if (s->void_img)
		mlx_destroy_image(s->mlx, s->void_img);
	if (s->pl1_img)
		mlx_destroy_image(s->mlx, s->pl1_img);
	if (s->pl2_img)
		mlx_destroy_image(s->mlx, s->pl2_img);
	if (s->arr)
		delete_array_(&(s->arr));
	if (s->line)
		ft_strdel(&(s->line));
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}
