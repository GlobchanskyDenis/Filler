/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:28:22 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/13 14:55:34 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	struct_free(t_data *s)
{
	if (!s)
		return ;
	fprint_fd(s->fd, "struct_free\n");
	if (s->line)
		ft_strdel(&(s->line));
	delete_array(&(s->map), s->map_size, s);
	delete_array(&(s->fig), s->fig_size, s);
	s->map_size = 0;
	s->fig_size = 0;
	fprint_fd(s->fd, "end of struct_free\n");
}

static int	init_players(t_data *s)
{
	if (!s)
		return (0);
	if ((s->line)[10] == '1')
	{
		s->id.me = 'O';
		s->id.pl = 'X';
	}
	else
	{
		s->id.me = 'X';
		s->id.pl = 'O';
	}
	ft_strdel(&(s->line));
	fprint_fd(s->fd, "My id is '%c' & '%c' enemy is '%c' & '%c'\n", \
			(s->id).me, (s->id).me + 32, (s->id).pl, (s->id).pl + 32);
	fprint_fd(s->fd, "Players was inited successfully\n");
	return (1);
}

static void	loop(t_data *s)
{
	int		flag;

	flag = 1;
	while (flag && s)
	{
		fprint_fd(s->fd, "\n>>>>>>>>>> new cycle <<<<<<<<<<\n\nInit map\n");
		if (!flag || !init_array(s))
			flag = 0;
		fprint_fd(s->fd, "Init figure\n");
		if (!flag || !init_array(s))
			flag = 0;
		if (flag)
		{
			if (algorithm(s))
				fprint("%d %d\n", (s->best).x, (s->best).y);
			else
				flag = 0;
		}
		struct_free(s);
	}
}

int			main(void)
{
	t_data	s;

	ft_bzero(&s, sizeof(t_data *));
	s.fd = open("log.txt", O_RDWR | O_CREAT);
	fprint_fd(s.fd, "Open log file success\nLog file fd = %d\n", s.fd);
	s.line = NULL;
	if (gnl(0, &(s.line)) && s.line && !ft_strncmp(s.line, "$$$ exec p", 9) && \
			ft_strlen(s.line) > 10 && (s.line[10] == '1' || s.line[10] == '2'))
	{
		fprint_fd(s.fd, "Head was readed\n");
		if (init_players(&s))
			loop(&s);
	}
	else
		fprint_fd(s.fd, "Invalid head\n");
	fprint_fd(s.fd, "Finishing filler player\n");
	struct_free(&s);
	close(s.fd);
	fprint("0 0\n");
	return (0);
}
