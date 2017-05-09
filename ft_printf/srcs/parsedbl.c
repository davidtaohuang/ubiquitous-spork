/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsedbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 00:18:01 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/26 00:18:01 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/ft_printf.h"

void	parsedbl(t_format *flags, va_list *args)
{
	if (LEN == 3)
	{
		flags->arg = (long double*)ft_memalloc(sizeof(long double));
		*(long double*)(flags->arg) = va_arg(*args, long double);
		FBLEN = sizeof(long double);
	}
	else
	{
		flags->arg = (double*)ft_memalloc(sizeof(double));
		*(double*)(flags->arg) = va_arg(*args, double);
		FBLEN = sizeof(double);
	}
	if (flags->precision < 0)
		flags->precision = 6;
	if (LT == 'e')
	{
		flags->ep = P;
		formatedbl(flags);
	}
	else
		formatdbl(flags);
	padnum(flags);
}
