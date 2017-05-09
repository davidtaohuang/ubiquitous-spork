/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 23:21:17 by dhuang            #+#    #+#             */
/*   Updated: 2016/09/28 17:25:53 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_print(long num, int fd)
{
	char	c;

	if (num < 10)
	{
		c = num + 48;
		write(fd, &c, 1);
		return ;
	}
	if (num >= 10)
		ft_print(num / 10, fd);
	ft_print(num % 10, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	c;

	num = n;
	c = '-';
	if (num < 0)
	{
		write(fd, &c, 1);
		num = num * -1;
	}
	ft_print(num, fd);
}
