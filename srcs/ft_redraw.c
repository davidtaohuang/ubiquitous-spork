/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redraw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:59:02 by dhuang            #+#    #+#             */
/*   Updated: 2017/05/10 14:59:02 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define CBUF 1.1
#define CBUF2 0.05

void	collision(t_mlxdata *d, t_vec move, int neg)
{
	t_vec	new;
	double	speed;
	
	if (d->sprint)
		speed = SSPD;
	else if (d->walk)
		speed = WSPD;
	else
		speed = MSPD;
	new.x = d->pos.x + (neg ? -move.x : move.x) * speed;
	new.y = d->pos.y + (neg ? -move.y : move.y) * speed;
	if (new.x < CBUF)
		new.x = CBUF;
	if (new.y < CBUF)
		new.y = CBUF;
	if (new.x > d->mapsize.x - CBUF)
		new.x = d->mapsize.x - CBUF;
	if (new.y > d->mapsize.y - CBUF)
		new.y = d->mapsize.y - CBUF;
	if (!d->wmap[(int)(new.x - CBUF2)][(int)(d->pos.y)] && !d->wmap[(int)(new.x + CBUF2)][(int)(d->pos.y)])
		d->pos.x = new.x;
	if (!d->wmap[(int)(d->pos.x)][(int)(new.y - CBUF2)] && !d->wmap[(int)(d->pos.x)][(int)(new.y + CBUF2)])
		d->pos.y = new.y;
}

void	ft_mlxredraw(t_mlxdata *d)
{
	mlx_clear_window(d->mlx, d->win);
	mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WINX, WINY);
	d->imgd = (unsigned int*)mlx_get_data_addr(d->img, &(d->bbp), &(d->line), &(d->endian));
	threadmanage(d);
}

int		ft_redraw(t_mlxdata *d)
{
	if (d->up == 1 && !d->down)
		collision(d, d->dir, 0);
	if (d->down == 1 && !d->up)
		collision(d, d->dir, 1);
	if (d->right == 1 && !d->left && d->shift)
		collision(d, d->plane, 0);
	if (d->left == 1 && !d->right && d->shift)
		collision(d, d->plane, 1);
	if (d->right == 1 && !d->left && !d->shift)
		d->angle -= RSPD;
	if (d->left == 1 && !d->right && !d->shift)
		d->angle += RSPD;
	if (d->angle >= 360)
		d->angle -= 360;
	if (d->angle < 0)
		d->angle += 360;
	d->dir.x = d->odir.x * cos(RA) - d->odir.y * sin(RA);
	d->dir.y = d->odir.x * sin(RA) + d->odir.y * cos(RA);
	d->plane.x = d->oplane.x * cos(RA) - d->oplane.y * sin(RA);
	d->plane.y = d->oplane.x * sin(RA) + d->oplane.y * cos(RA);
	if ((d->left ^ d->right) || (d->up ^ d->down))
		ft_mlxredraw(d);
	return (1);
}
