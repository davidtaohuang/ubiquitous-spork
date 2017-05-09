/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:53:34 by dhuang            #+#    #+#             */
/*   Updated: 2017/05/01 21:53:34 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_vec	fwallsetup(t_mlxdata *d, int side)
{
	t_vec	fwall;

	if (!side && d->raydir.x > 0)
	{
		fwall.x = d->map.x;
		fwall.y = d->map.y + d->wallx;
	}
	else if (!side && d->raydir.x < 0)
	{
		fwall.x = d->map.x + 1.0;
		fwall.y = d->map.y + d->wallx;
	}
	else if (side && d->raydir.y > 0)
	{
		fwall.x = d->map.x + d->wallx;
		fwall.y = d->map.y;
	}
	else
	{
		fwall.x = d->map.x + d->wallx;
		fwall.y = d->map.y + 1.0;
	}
	return (fwall);
}

void	fccalc(t_mlxdata *d, t_vec fwall, int j, int i)
{
	double	cdist;
	double	weight;
	t_vec	cfloor;
	t_vec	tex;
	t_col	color;

	cdist = WINY / ((double)2.0 * j - WINY);
	weight = cdist / d->wall;
	cfloor.x = weight * fwall.x + (1.0 - weight) * d->pos.x;
	cfloor.y = weight * fwall.y + (1.0 - weight) * d->pos.y;
	tex.x = (int)(cfloor.x * TW) % TW;
	tex.y = (int)(cfloor.y * TH) % TH;
	
	color.c = d->ctex->imgd[TW * (int)tex.y + (int)tex.x];
	*(d->imgd + (WINY - j) * WINX + i) = color.c;
	color.c = d->ftex->imgd[TW * (int)tex.y + (int)tex.x];
	*(d->imgd + j * WINX + i) = color.c;
}

void	drawfc(t_mlxdata *d, int side, int drawend, int i)
{
	t_vec	fwall;
	int		j;

	fwall = fwallsetup(d, side);
	if (drawend < 0)
		drawend = WINY;
	j = drawend + 1;
	while (j < WINY)
	{
		fccalc(d, fwall, j, i);
		j++;
	}
}
