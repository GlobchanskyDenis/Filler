/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:05:10 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/08/30 13:02:58 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		print_array(char **arr, int size, t_data *s, char *message)
{
	int		i;

	if (!arr || size < 1)
	{
		fprint_fd(s->fd, "empty array '%s'. Error\n", message);
		return ;
	}
	i = 0;
	fprint_fd(s->fd, "======= print array %s =======\n", message);
	while (i < size)
	{
		if (arr[i])
			fprint_fd(s->fd, "'%s'\n", arr[i]);
		i++;
	}
	fprint_fd(s->fd, "==== end of print array %s ===\n", message);
}
