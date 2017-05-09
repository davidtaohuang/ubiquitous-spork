/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 17:14:42 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:51:03 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long	ft_makenum(const char *str, int b, int i)
{
	long	n;

	n = 0;
	if (b > 10)
	{
		while ((str[i] >= '0' && str[i] <= '9') ||
			(str[i] >= 'A' && str[i] <= ('A' + b - 10)))
		{
			if (str[i] >= '0' && str[i] <= '9')
				n = b * n - (str[i++] - '0');
			if (str[i] >= 'A' && str[i] <= ('A' + b - 10))
				n = b * n - (str[i++] - 'A' + 10);
		}
	}
	else if (b > 0)
	{
		while (str[i] >= '0' && str[i] <= ('0' + b))
			n = b * n - (str[i++] - '0');
	}
	return (n);
}

int			ft_atoibase(const char *str, int b)
{
	int		i;
	int		neg;
	long	n;

	if (b <= 1)
		return (0);
	i = 0;
	neg = -1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = 1;
		i++;
	}
	n = ft_makenum(str, b, i);
	n *= neg;
	return (n);
}
