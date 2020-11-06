/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcsper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opidgey <opidgey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:24:23 by opidgey           #+#    #+#             */
/*   Updated: 2020/08/04 12:25:00 by opidgey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printchar(t_pi *data, va_list args)
{
	unsigned char	c;

	c = va_arg(args, int);
	if (data->flags & MINUS)
		data->length += write(1, &c, 1);
	while (--data->width > 0)
	{
		if (data->flags & ZERO)
			data->length += write(1, "0", 1);
		else
			data->length += write(1, " ", 1);
	}
	if (!(data->flags & MINUS))
		data->length += write(1, &c, 1);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (str)
		while (str[i] != '\0')
			i++;
	return (i);
}

void	printstring(t_pi *data, va_list args)
{
	char	*str;
	int		len;
	int		diff;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if ((data->flags & PRECISION) && len > data->precision)
		len = data->precision;
	diff = data->width - len;
	if (data->flags & MINUS)
		data->length += write(1, str, len);
	while (diff-- > 0)
		if (data->flags & ZERO)
			data->length += write(1, " ", 1);
		else
			data->length += write(1, " ", 1);
	if (!(data->flags & MINUS))
		data->length += write(1, str, len);
}

void	printpercent(t_pi *data)
{
	if (data->flags & MINUS)
		data->length += write(1, "%%", 1);
	while (--data->width > 0)
	{
		if (data->flags & ZERO)
			data->length += write(1, "0", 1);
		else
			data->length += write(1, " ", 1);
	}
	if (!(data->flags & MINUS))
		data->length += write(1, "%%", 1);
}
