/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnum2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opidgey <opidgey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:25:25 by opidgey           #+#    #+#             */
/*   Updated: 2020/08/04 12:30:20 by opidgey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				lenmax(long long int num, int len, int base, t_pi *data)
{
	if (data->spec == 'p')
	{
		data->length += write(1, "0x", 2);
		ft_putnbr(num, len - 2, base, data);
	}
	else if (num < 0)
	{
		data->length += write(1, "-", 1);
		ft_putnbr(-num, len - 1, base, data);
	}
	else
		ft_putnbr(num, len, base, data);
	return (len);
}

void			printlenprecnum(int diff2,\
long long int num, int len, t_pi *data)
{
	int			base;

	if (data->spec == 'p')
	{
		data->length += write(1, "0x", 2);
		data->spec = 'x';
		len -= 2;
	}
	if (num < 0)
	{
		data->length += write(1, "-", 1);
		num = -num;
		len--;
	}
	while (diff2-- > 0)
		data->length += write(1, "0", 1);
	if (data->spec == 'x' || data->spec == 'X')
		base = 16;
	else
		base = 10;
	ft_putnbr(num, len, base, data);
}

long long int	getnumber(va_list args, char spec)
{
	if (spec == 'd' || spec == 'i')
		return (va_arg(args, int));
	if (spec == 'u' || spec == 'x' || spec == 'X')
		return (va_arg(args, unsigned int));
	if (spec == 'p')
		return (va_arg(args, size_t));
	return (0);
}

void			printnumber(t_pi *data, va_list args, int base)
{
	long long int	num;
	int				len;
	int				diff[2];

	num = getnumber(args, data->spec);
	len = numlen(num, base);
	if (num == 0 && data->flags & PRECISION && data->precision == 0)
		len = 0;
	if (data->flags & PRECISION)
		data->flags &= (~ZERO);
	len = (data->spec == 'p') ? len + 2 : len;
	if (len > data->precision && len > data->width)
	{
		lenmax(num, len, base, data);
		return ;
	}
	if (data->spec == 'p')
		data->precision += 2;
	managediffs(diff, len, data, num);
	if (data->flags & MINUS)
		printlenprecnum(diff[1], num, len, data);
	while (diff[0]-- > 0)
		data->length += write(1, " ", 1);
	if (!(data->flags & MINUS))
		printlenprecnum(diff[1], num, len, data);
}
