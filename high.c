/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opidgey <opidgey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:59:48 by opidgey           #+#    #+#             */
/*   Updated: 2020/08/06 15:59:49 by opidgey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			isin(char c, char *str)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static void	prestruct(const char **format, va_list args, t_pi *data)
{
	manageflags(data, format);
	managewidth(data, format, args);
	manageprecision(data, format, args);
	managespecification(data, format);
}

static int	writespec(const char **ptr_format, va_list args, t_pi *data)
{
	prestruct(ptr_format, args, data);
	if (data->spec == 'c')
		printchar(data, args);
	else if (data->spec == 's')
		printstring(data, args);
	else if (isin(data->spec, "diu"))
		printnumber(data, args, 10);
	else if (isin(data->spec, "xXp"))
		printnumber(data, args, 16);
	else if (data->spec == '%')
		printpercent(data);
	return (data->length);
}

void		initdata(t_pi *data)
{
	data->flags = 0;
	data->width = 0;
	data->precision = 0;
	data->spec = 0;
	data->length = 0;
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	t_pi	data;

	if (!format)
		return (-1);
	va_start(args, format);
	initdata(&data);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			writespec(&format, args, &data);
		}
		else
		{
			data.length += write(1, format, 1);
			format++;
		}
	}
	va_end(args);
	return (data.length);
}
