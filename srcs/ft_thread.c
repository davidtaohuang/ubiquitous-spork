/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 19:39:24 by dhuang            #+#    #+#             */
/*   Updated: 2017/05/10 19:39:24 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	These functions direct the threads that calculate vertical bands of the
**	MLX image window.
**
**	Bands are assigned based on the thread id and width of the image window,
**	thus it is imperative that the width of the image window in pixels (WINX)
**	is evenly divisible by THREAD_COUNT.
*/

static void	*raycast(void *arg)
{
	t_thread	*data;
	int			i;
	int			end;

	data = (t_thread*)arg;
	i = data->tid * CHUNK;
	end = i + CHUNK;
	while (i < end)
		raycaster(data->d, i++);
	pthread_exit(NULL);
}

void		threadmanage(t_mlxdata *d)
{
	pthread_t	thr[THREAD_COUNT];
	t_thread	tdata[THREAD_COUNT];
	int			i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		tdata[i].tid = i;
		tdata[i].d = d;
		pthread_create(&thr[i], NULL, raycast, &tdata[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
		pthread_join(thr[i++], NULL);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}
