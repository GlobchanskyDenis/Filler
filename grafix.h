/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:19:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/12 21:17:36 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAFIX_H
# define GRAFIX_H

# include "mlx/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# define OFFSET 50
# define ESCAPE 53

typedef struct	s_graf
{
	char	**old_arr;
	char	**arr;
	void	*mlx;
	void	*win;
	void	*pl1_img;
	void	*pl2_img;
	void	*void_img;
	void	*bg_img;
	int		win_width;
	int		win_height;
	int		arr_width;
	int		arr_height;
	int		img_width;
	int		img_height;
	char	*pl1;
	char	*pl2;
	int		pl1_score;
	int		pl2_score;
	int		pl1_color;
	int		pl2_color;
	int		is_pause;
	char	*line;
	int		is_end;
}				t_graf;

void			paint_first_array(t_graf *s, char **arr);
void			paint_new_array(t_graf *s, char **arr, char **old_arr);
void			gnl(int fd, char **line);
void			*make_new_img(t_graf *s, int color);
void			fill_img_color(char *img, size_t count, int color);
void			delete_array_(char ***arr);
void			free_and_exit(t_graf *s);
char			**start_read_input(t_graf *s);
void			read_input(t_graf *s);
void			read_until_strncmp(char **line, const char *str);
int				key_escape(int key, t_graf *s);
int				mouse_pause(int param, int x, int y, t_graf *s);
int				loop_hook(t_graf *s);

#endif
