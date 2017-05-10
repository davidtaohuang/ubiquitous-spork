/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 20:23:00 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/24 20:23:00 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	maketex(t_mlxdata *d, char *str, t_tex **tex)
{
	t_tex	*tmp;

	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
	tmp->img = mlx_xpm_file_to_image(d->mlx, str, &tmp->w, &tmp->h);
	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp, &tmp->line,
		&tmp->endian);
	*tex = tmp;
}

void	maketextures(t_mlxdata *d)
{
	maketex(d, "textures/wood.xpm", &d->ftex);
	maketex(d, "textures/trapdoor.xpm", &d->ctex);
	maketex(d, "textures/web.xpm", &d->wtex);
}
