/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:03:58 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/19 19:03:58 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	These functions output error codes to the console on STD_ERROR and free
**	allocated memory on program exit.
*/

void	ft_puterror(int code)
{
	if (code == 1)
		ft_putendl_fd("Usage: ./wolf3d [map]\n", 2);
	if (code == 2)
		ft_putendl_fd("Invalid map file\n", 2);
}

void	ft_freemlxdata(t_mlxdata *d)
{
	int		i;

	if (d->wmap)
	{
		i = 0;
		while (i < d->mapsize.y)
		{
			ft_memdel((void**)&d->wmap[i]);
			i++;
		}
		ft_memdel((void**)&d->wmap);
	}
	mlx_destroy_image(d->mlx, d->wtex->img);
	mlx_destroy_image(d->mlx, d->ctex->img);
	mlx_destroy_image(d->mlx, d->ftex->img);
	ft_memdel((void**)&d->wtex);
	ft_memdel((void**)&d->ctex);
	ft_memdel((void**)&d->ftex);
	ft_memdel((void**)&d);
}

void	ft_freetmp(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		ft_memdel((void**)&tmp[i]);
		i++;
	}
	ft_memdel((void**)&tmp);
}

void	ft_linecleanup(char **tmp)
{
	ft_freetmp(tmp);
	ft_puterror(2);
	exit(1);
}

void	ft_cleanall(t_mlxdata *d, char **tmp)
{
	ft_freemlxdata(d);
	ft_linecleanup(tmp);
}
