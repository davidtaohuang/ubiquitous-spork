/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_khooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 19:53:06 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/17 19:53:06 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	Key 53 	= escape, triggers freeing of memory and exits program
**
**	Key 126	= up arrow, moves forwards
**	Key 125	= down arrow, moves backwards
**	Key 123 = left, turns to the left
**	Key 124 = right, turns to the right
**
**	Key 13	= w, moves forwards
**	Key 1	= s, moves forwards
**	Key 2	= d, turns to the right
**	Key 0	= a, turns to the left
**
**	Key 257 = shift, hold to sprint (increased movement speed)
**	Key 256 = left control, hold to walk (decreased movement speed)
**	Key 49	= spacebar, hold to walk (decreased movement speed)
**	Key 6	= z, hold to strafe left or right (in combination with the keys)
**	Key 48	= tab, toggles display of map location in mlx window and key debug
**			  info in the terminal window
*/

static void	ft_keyexit(t_mlxdata *d)
{
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	ft_freemlxdata(d);
	exit(1);
}

int			exit_hook(int key, t_mlxdata *d)
{
	(void)key;
	(void)d;
	exit(1);
	return (0);
}

int			ft_kdown(int key, t_mlxdata *d)
{
	if (key == 48)
	{
		d->info = (!(d->info) ? 1 : 0);
		ft_mlxredraw(d);
	}
	if (d->info)
		ft_printf("Key = %d\n", key);
	if (key == 126 || key == 13)
		d->up = 1;
	if (key == 125 || key == 1)
		d->down = 1;
	if (key == 124 || key == 2)
		d->right = 1;
	if (key == 123 || key == 0)
		d->left = 1;
	if (key == 6)
		d->shift = 1;
	if (key == 257)
		d->sprint = 1;
	if (key == 256 || key == 49)
		d->walk = 1;
	if (key == 53)
		ft_keyexit(d);
	return (0);
}

int			ft_kup(int key, t_mlxdata *d)
{
	if (key == 126 || key == 13)
		d->up = 0;
	if (key == 125 || key == 1)
		d->down = 0;
	if (key == 124 || key == 2)
		d->right = 0;
	if (key == 123 || key == 0)
		d->left = 0;
	if (key == 6)
		d->shift = 0;
	if (key == 257)
		d->sprint = 0;
	if (key == 256 || key == 49)
		d->walk = 0;
	return (0);
}
