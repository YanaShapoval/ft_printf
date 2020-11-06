/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opidgey <opidgey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:16:06 by opidgey           #+#    #+#             */
/*   Updated: 2020/08/06 16:16:08 by opidgey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	manageflags(t_pi *data, const char **format)
{
	data->flags = 0;
	if (!format || !data)
		return ;
	while (isin(**format, "#0 -+"))
	{
		if (**format == '#')
			data->flags |= SHARP;
		else if (**format == '0' && !(data->flags & MINUS))
			data->flags |= ZERO;
		else if (**format == '-')
			data->flags = (data->flags | MINUS) & (~ZERO);
		else if (**format == ' ')
			data->flags |= SPACE;
		else if (**format == '+')
			data->flags = (data->flags | PLUS) & (~SPACE);
		(*format)++;
	}
}

void	managewidth(t_pi *data, const char **format, va_list args)
{
	if (**format == '*')
	{
		(*format)++;
		if ((data->width = va_arg(args, int)) < 0)
		{
			data->width *= -1;
			data->flags = (data->flags | MINUS) & (~ZERO);
		}
	}
	else
	{
		data->width = 0;
		while (**format >= '0' && **format <= '9')
		{
			data->width = data->width * 10 + **format - '0';
			(*format)++;
		}
	}
}

void	manageprecision(t_pi *data, const char **format, va_list args)
{
	data->precision = 0;
	if (**format == '.')
	{
		(*format)++;
		data->flags |= PRECISION;
		if (**format == '*')
		{
			(*format)++;
			if ((data->precision = va_arg(args, int)) < 0)
				data->flags &= (~PRECISION);
		}
		else
		{
			while (**format >= '0' && **format <= '9')
			{
				data->precision = data->precision * 10 + **format - '0';
				(*format)++;
			}
		}
	}
}

void	managespecification(t_pi *data, const char **format)
{
	data->spec = **format;
	if (isin(**format, "cspdiuxX%%"))
		(*format)++;
}
