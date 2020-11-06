/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnum1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opidgey <opidgey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:55:48 by opidgey           #+#    #+#             */
/*   Updated: 2020/08/06 15:55:50 by opidgey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		numlen(long long int n, int base)
{
	int		len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n / base)
	{
		n = n / base;
		len++;
	}
	return (len);
}

void	ft_putnbr(long long int n, int pow, int base, t_pi *data)
{
	char	c;

	if (pow <= 0)
		return ;
	if (pow > 1)
		ft_putnbr(n / base, pow - 1, base, data);
	if (data->spec == 'X')
		c = ARRAY88[n % base];
	else
		c = ARRAY120[n % base];
	data->length += write(1, &c, 1);
}

void	managediffs(int *diffs, int len,\
t_pi *data, long long int num)
{
	int	flag;

	flag = 0;
	if (num < 0)
	{
		flag = 1;
		len--;
	}
	diffs[1] = (data->flags & PRECISION) ? data->precision - len : 0;
	if (data->width > len && data->width > data->precision)
		diffs[0] = ((diffs[1] > 0) ? data->width - data->precision \
		: data->width - len) - flag;
	else
		diffs[0] = 0;
	if (data->flags & ZERO)
	{
		diffs[1] += diffs[0];
		diffs[0] = 0;
	}
}
