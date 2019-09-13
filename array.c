/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:58:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/13 14:58:22 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char	**allocate_array(int size, t_data *s)
{
	char	**dst;
	int		i;

	if (size < 1 || !s)
		return (NULL);
	fprint_fd(s->fd, "start to allocating of array\n");
	dst = NULL;
	if (!(dst = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size + 1)
		dst[i++] = NULL;
	fprint_fd(s->fd, "end of allocation of array\n");
	return (dst);
}

void		delete_array(char ***arr, int size, t_data *s)
{
	int		i;

	if (!s || !arr || !(*arr) || size < 1)
		return ;
	fprint_fd(s->fd, "Start to delete array\n");
	i = 0;
	while (i < size)
	{
		if ((*arr)[i])
			free((*arr)[i]);
		(*arr)[i++] = NULL;
	}
	free(*arr);
	*arr = NULL;
	fprint_fd(s->fd, "Array was deleted\n");
}

static char	**fill_map(char **arr, int size, t_data *s)
{
	int		i;

	if (!s || size < 1 || !arr)
	{
		delete_array(&arr, size, s);
		return (NULL);
	}
	fprint_fd(s->fd, "Filling map\n");
	i = 0;
	while (i < size && gnl(0, &(s->line)) > 0)
	{
		fprint_fd(s->fd, "Read line << '%s' i = %d\n", s->line, i);
		arr[i++] = ft_strdup((char *)(s->line) + 4);
		free(s->line);
		s->line = NULL;
	}
	if (i == size)
		fprint_fd(s->fd, "Map was filled correctly\n");
	else
		fprint_fd(s->fd, "Map was filled incorrectly. Error\n");
	s->map = arr;
	s->map_size = size;
	fprint_fd(s->fd, "End of filling map\n");
	return (arr);
}

static char	**fill_fig(char **arr, int size, t_data *s)
{
	int		i;

	if (!s || size < 1 || !arr)
	{
		delete_array(&arr, size, s);
		return (NULL);
	}
	fprint_fd(s->fd, "Filling figure\n");
	i = 0;
	while (i < size && gnl(0, &(s->line)) > 0)
	{
		fprint_fd(s->fd, "Read line << '%s' i = %d\n", s->line, i);
		arr[i++] = s->line;
		s->line = NULL;
	}
	if (i == size)
		fprint_fd(s->fd, "Figure was filled correctly\n");
	else
		fprint_fd(s->fd, "Figure was filled incorrectly. Error\n");
	s->fig = arr;
	s->fig_size = size;
	fprint_fd(s->fd, "End of filling figure\n");
	return (arr);
}

char		**init_array(t_data *s)
{
	int		size;

	if (!s || !gnl(0, &(s->line)) || !(s->line))
		return (NULL);
	if (!ft_strncmp(s->line, "Plateau", 7) && (size = ft_atoi(&((s->line)[8]))))
	{
		fprint_fd(s->fd, "Size = %d\nRead & del << '%s'\n", size, s->line);
		ft_strdel((&(s->line)));
		gnl(0, &(s->line));
		fprint_fd(s->fd, "Read & del << '%s'\n", s->line);
		ft_strdel(&(s->line));
		return (fill_map(allocate_array(size, s), size, s));
	}
	if (!ft_strncmp(s->line, "Piece", 5) && \
			(size = ft_atoi(&((s->line)[6]))))
	{
		fprint_fd(s->fd, "Size = %d\nRead & del << '%s'\n", size, s->line);
		ft_strdel(&(s->line));
		return (fill_fig(allocate_array(size, s), size, s));
	}
	fprint_fd(s->fd, "data is invalid\n");
	return (NULL);
}
