/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ranks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:13:05 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/13 14:56:55 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_can_put_symb2(char **arr, char symb, t_data *s, t_pos p)
{
	char	old;

	if (!arr || !s)
		return (0);
	if (symb > 1)
		old = symb - 1;
	else
		old = (s->id).pl;
	if (arr[p.x][p.y + 1] == old || arr[p.x][p.y + 1] == (s->id).pl + 32)
		return (1);
	if (arr[p.x + 1] && p.y != 0 && (arr[p.x + 1][p.y - 1] == old || \
				arr[p.x + 1][p.y - 1] == (s->id).pl + 32))
		return (1);
	if (arr[p.x + 1] && (arr[p.x + 1][p.y] == old || \
				arr[p.x + 1][p.y] == (s->id).pl + 32))
		return (1);
	if (arr[p.x + 1] && (arr[p.x + 1][p.y + 1] == old || \
				arr[p.x + 1][p.y + 1] == (s->id).pl + 32))
		return (1);
	return (0);
}

static int	is_can_put_symb(char **arr, char symb, t_data *s, t_pos p)
{
	char	old;

	if (!arr || !s || arr[p.x][p.y] != '.')
		return (0);
	if (symb > 1)
		old = symb - 1;
	else
		old = (s->id).pl;
	if (p.x != 0 && p.y != 0 && (arr[p.x - 1][p.y - 1] == old || \
				arr[p.x - 1][p.y - 1] == (s->id).pl + 32))
		return (1);
	if (p.x != 0 && (arr[p.x - 1][p.y] == old || \
				arr[p.x - 1][p.y] == (s->id).pl + 32))
		return (1);
	if (p.x != 0 && (arr[p.x - 1][p.y + 1] == old || \
				arr[p.x - 1][p.y + 1] == (s->id).pl + 32))
		return (1);
	if (p.y != 0 && (arr[p.x][p.y - 1] == old || \
				arr[p.x][p.y - 1] == (s->id).pl + 32))
		return (1);
	return (is_can_put_symb2(arr, symb, s, p));
}

void		fill_map_by_ranks(char **arr, char symb, t_data *s)
{
	t_pos	p;
	int		flag;

	if (!s || !arr || symb == '.')
		return ;
	p.x = 0;
	flag = 0;
	fprint_fd(s->fd, "try to fill map by %d\n", (int)symb);
	while (arr[p.x])
	{
		p.y = 0;
		while (arr[p.x][p.y])
		{
			if (is_can_put_symb(arr, symb, s, p))
			{
				arr[p.x][p.y] = symb;
				flag = 1;
			}
			p.y++;
		}
		p.x++;
	}
	print_array(arr, s->map_size, s, "map algorithm");
	if (flag)
		fill_map_by_ranks(arr, symb + 1, s);
}
