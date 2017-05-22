/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getaline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 19:12:02 by dhuang            #+#    #+#             */
/*   Updated: 2017/05/21 19:12:02 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	I made getaline because get_next_line is over-engineered for what I need
**	it to do in the context of this program and also because of the
**	over-engineering it is inherently leaky in certain situations. This should
**	be much more robust.
*/

static int	ft_read(int fd, char **line)
{
	char	*buf;
	int		i;

	buf = ft_strnew(1);
	i = 0;
	while (read(fd, buf, 1))
	{
		i++;
		*line = ft_strjoinreplace(*line, buf);
		if (buf[0] == '\n')
			break ;
		ft_bzero(buf, 2);
	}
	ft_memdel((void**)&buf);
	return (i);
}

int			getaline(const int fd, char **line)
{
	int			i;

	if (!line || fd < 0)
		return (-1);
	*line = ft_strnew(0);
	i = ft_read(fd, line);
	if (i == 0)
		ft_memdel((void**)line);
	return (i);
}
