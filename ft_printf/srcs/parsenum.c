/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsenum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 00:29:01 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/26 00:29:01 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	parsehnum(t_format *flags, va_list *args)
{
	if (LEN == -2)
	{
		flags->arg = (char*)ft_memalloc(sizeof(char));
		*(char*)(flags->arg) = va_arg(*args, int);
		FBLEN = sizeof(char);
	}
	else if (LEN == -1)
	{
		flags->arg = (short*)ft_memalloc(sizeof(short));
		*(short*)(flags->arg) = va_arg(*args, int);
		FBLEN = sizeof(short);
	}
}

void		parsenum(t_format *flags, va_list *args)
{
	if (TYPE == 'D' || LEN == 1)
	{
		flags->arg = (long*)ft_memalloc(sizeof(long));
		*(long*)(flags->arg) = va_arg(*args, long);
		FBLEN = sizeof(long);
	}
	else if (LEN < 0)
		parsehnum(flags, args);
	else if (LEN == 0)
	{
		flags->arg = (int*)ft_memalloc(sizeof(int));
		*(int*)(flags->arg) = va_arg(*args, int);
		FBLEN = sizeof(int);
	}
	else if (LEN == 2)
	{
		flags->arg = (long long*)ft_memalloc(sizeof(long long));
		*(long long*)(flags->arg) = va_arg(*args, long long);
		FBLEN = sizeof(long long);
	}
	formatnum(flags);
	padnum(flags);
}
