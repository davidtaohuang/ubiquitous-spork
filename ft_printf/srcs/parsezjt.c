/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsezjt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 21:06:40 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/25 21:06:40 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	parseagain(t_format *flags, va_list *args, t_data *pf)
{
	LEN = 0;
	parseswitch(flags, args, pf);
}

void		parsezjt(t_format *flags, va_list *args, t_data *pf)
{
	if (LT == 'u' || LT == 'd' || LT == 'i' || LT == 'o' || LT == 'x' ||
		LT == 'b')
	{
		if (LEN == 4)
		{
			flags->arg = (size_t*)ft_memalloc(sizeof(size_t));
			*(size_t*)(flags->arg) = va_arg(*args, size_t);
			FBLEN = sizeof(size_t);
		}
		else if (LEN == 5)
		{
			flags->arg = (intmax_t*)ft_memalloc(sizeof(intmax_t));
			*(intmax_t*)(flags->arg) = va_arg(*args, intmax_t);
			FBLEN = sizeof(intmax_t);
		}
		else if (LEN == 6)
		{
			flags->arg = (ptrdiff_t*)ft_memalloc(sizeof(ptrdiff_t));
			*(ptrdiff_t*)(flags->arg) = va_arg(*args, ptrdiff_t);
			FBLEN = sizeof(ptrdiff_t);
		}
		formatzjt(flags);
	}
	else
		parseagain(flags, args, pf);
}
