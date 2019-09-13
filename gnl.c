/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:56:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/08/21 13:25:11 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		gnl(int fd, char **line)
{
	int		ret;
	char	*tmp;
	char	buf[2];

	if (!line)
		return (-1);
	*line = ft_strnew(0);
	ret = 0;
	ft_bzero(buf, 2);
	while ((read(fd, buf, 1) > 0) && buf[0] != '\n' && buf[0] != '\0')
	{
		ret++;
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
	}
	return (ret);
}
