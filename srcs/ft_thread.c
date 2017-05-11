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

static void	mlxputinfo(t_mlxdata *d)
{
	char		*str;

	ft_asprintf(&str, "X = %.2f Y = %.2f", d->pos.x, d->pos.y);
	mlx_string_put(d->mlx, d->win, 0, 0, 0x00FFFFFF, str);
	free(str);
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
	if (d->info)
		mlxputinfo(d);
}
