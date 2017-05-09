/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseunum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 00:51:02 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/26 00:51:02 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	padunum(t_format *flags)
{
	if (LT == 'o' && FGN)
		padoct(flags);
	else if (LT == 'x' && FGN && !(FBLEN == 1 && *((char*)ARG) == '0'))
		padhex(flags);
	else
		padnum(flags);
}

static void	parsehunum(t_format *flags, va_list *args)
{
	if (LEN == -2)
	{
		flags->arg = (unsigned char*)ft_memalloc(sizeof(unsigned char));
		*(unsigned char*)(flags->arg) = va_arg(*args, unsigned int);
		FBLEN = sizeof(char);
	}
	else if (LEN == -1)
	{
		flags->arg = (unsigned short*)ft_memalloc(sizeof(unsigned short));
		*(unsigned short*)(flags->arg) = va_arg(*args, unsigned int);
		FBLEN = sizeof(unsigned short);
	}
}

void		parseunum(t_format *flags, va_list *args)
{
	if (TYPE == 'U' || TYPE == 'B' || TYPE == 'O')
		LEN = 1;
	if (LEN == 1)
	{
		flags->arg = (unsigned long*)ft_memalloc(sizeof(unsigned long));
		*(unsigned long*)(flags->arg) = va_arg(*args, unsigned long);
		FBLEN = sizeof(unsigned long);
	}
	else if (LEN < 0)
		parsehunum(flags, args);
	else if (!LEN)
	{
		flags->arg = (unsigned int*)ft_memalloc(sizeof(unsigned int));
		*(unsigned int*)(flags->arg) = va_arg(*args, unsigned int);
		FBLEN = sizeof(unsigned int);
	}
	else if (LEN == 2)
	{
		flags->arg = (unsigned long*)ft_memalloc(sizeof(unsigned long long));
		*(unsigned long long*)(flags->arg) = va_arg(*args, unsigned long long);
		FBLEN = sizeof(unsigned long long);
	}
	formatunum(flags);
	padunum(flags);
}
