/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 21:32:01 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 09:53:57 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

static int		free_lines(t_line **nl)
{
	char **tmp;

	if (*nl)
	{
		if ((*nl)->fid)
			ft_memdel((void**)&((*nl)->fid));
		if ((*nl)->b)
		{
			tmp = (*nl)->b;
			while (*tmp)
				ft_memdel((void**)&(*tmp++));
			ft_memdel((void**)((*nl)->b));
		}
		ft_memdel((void**)nl);
	}
	return (-1);
}

static t_line	*ft_setup(const int fd)
{
	t_line	*nl;

	nl = (t_line*)malloc(sizeof(t_line));
	if (!nl)
		return (0);
	nl->b = ft_memalloc(sizeof(char*) * 2);
	if (!(nl->b))
		return (0);
	nl->fid = (int*)ft_memalloc(sizeof(int));
	nl->b[0] = ft_strnew(0);
	if (!(nl->fid) || !(nl->b[0]))
		return (0);
	nl->fid[0] = fd;
	nl->fn = 1;
	nl->afd = 1;
	return (nl);
}

static int		ft_resize(const int fd, t_line *nl)
{
	int		i;

	i = 0;
	while (i < nl->fn)
	{
		if (nl->fid[i] == fd)
			return (i);
		i++;
	}
	nl->b = (char**)ft_mrlc(nl->b, sizeof(char*) * (i + 1),
		sizeof(char*) * (i + 2));
	if (!(nl->b))
		return (-1);
	nl->fid = (int*)ft_mrlc(nl->fid, sizeof(int) * (i), sizeof(int) * (i + 1));
	nl->b[i] = ft_strnew(0);
	if (!nl->fid || !nl->b[i])
		return (-1);
	nl->fid[i] = fd;
	nl->fn++;
	nl->afd++;
	return (i);
}

static int		ft_read(int a, t_line *nl, char **line, int fi)
{
	char	*n;
	char	*tmp;

	if ((n = ft_memchr(nl->b[fi], 10, ft_strlen(nl->b[fi]))))
	{
		*line = ft_strnew(n - nl->b[fi]);
		ft_memmove(*line, nl->b[fi], n - nl->b[fi]);
		tmp = ft_strdup(n + 1);
		ft_memdel((void**)&nl->b[fi]);
		nl->b[fi] = tmp;
		return (1);
	}
	tmp = ft_strnew(BUFF_SIZE);
	if ((a = read(nl->fid[fi], tmp, BUFF_SIZE)) > 0)
		nl->b[fi] = ft_strjoin(nl->b[fi], tmp);
	ft_memdel((void**)&tmp);
	if (a < BUFF_SIZE && !(ft_memchr(nl->b[fi], 10, ft_strlen(nl->b[fi]))))
	{
		if (a == -1)
			return (-1);
		*line = ft_strdup(nl->b[fi]);
		ft_bzero(nl->b[fi], ft_strlen(nl->b[fi]));
		return (ft_strlen(*line) ? 1 : 0);
	}
	return (2);
}

int				get_next_line(const int fd, char **line)
{
	static t_line	*nl;
	int				e;
	int				fi;

	if (!line || fd < 0)
		return (-1);
	if (!nl)
	{
		if (!(nl = ft_setup(fd)))
			return (free_lines(&nl));
	}
	if ((fi = ft_resize(fd, nl)) < 0)
		return (free_lines(&nl));
	e = 2;
	while (e > 1)
		e = ft_read(0, nl, line, fi);
	if (e < 0)
		return (-1);
	if (!e)
		nl->afd--;
	if (!(nl->afd))
		free_lines(&nl);
	return (e);
}
