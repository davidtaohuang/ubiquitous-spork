/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 22:39:27 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:51:23 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "includes/libft.h"

static int	ft_length(long long n)
{
	int			i;

	i = 0;
	if (!n)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_digits(char *a, long long num, int len)
{
	if (!num)
		a[--len] = 48;
	while (num)
	{
		a[--len] = num % 10 + 48;
		num /= 10;
	}
}

static int	minchecker(long long *num)
{
	if (*num == INT64_MIN)
	{
		*num += 1;
		return (1);
	}
	else
		return (0);
}

char		*ft_itoa(long long n)
{
	int			len;
	int			mincheck;
	long long	num;
	char		*a;

	num = n;
	mincheck = 0;
	if (n < 0)
	{
		mincheck = minchecker(&num);
		num *= -1;
	}
	len = ft_length(num);
	if (n < 0)
		len += 1;
	a = ft_strnew(len);
	if (!a)
		return (a);
	if (n < 0)
		a[0] = 45;
	ft_digits(a, num, len);
	if (mincheck)
		a[--len]++;
	return (a);
}
