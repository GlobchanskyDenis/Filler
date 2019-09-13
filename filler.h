/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:20:25 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/13 15:01:08 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/libft.h"

typedef struct	s_id
{
	char	me;
	char	pl;
}				t_id;

typedef struct	s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct	s_data
{
	t_id	id;
	t_pos	cur;
	t_pos	best;
	char	*line;
	char	**map;
	char	**fig;
	int		map_size;
	int		fig_size;
	int		fd;
	int		flag;
	int		best_count;
	int		cur_count;
}				t_data;

int				gnl(int fd, char **line);
char			**init_array(t_data *s);
void			delete_array(char ***arr, int size, t_data *s);
void			print_array(char **arr, int size, t_data *s, char *message);
void			fill_map_by_ranks(char **arr, char symb, t_data *s);
t_pos			init_offset(char **fig, t_data *s);
int				is_can_put_figure(char **fig, t_pos m, t_pos o, t_data *s);
int				algorithm(t_data *s);
char			**alloc_cpy_fig(char **fig);

#endif
