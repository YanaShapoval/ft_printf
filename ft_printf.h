/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opidgey <opidgey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:18:42 by opidgey           #+#    #+#             */
/*   Updated: 2020/08/04 12:18:46 by opidgey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define MINUS		0b00000001
# define PLUS		0b00000010
# define SPACE		0b00000100
# define SHARP		0b00001000
# define ZERO		0b00010000
# define PRECISION	0b00100000
# define ARRAY88	"0123456789ABCDEF"
# define ARRAY120	"0123456789abcdef"

typedef struct	s_parse_info {
	unsigned char	flags;
	int				width;
	int				precision;
	char			spec;
	int				length;
}				t_pi;

void			printchar(t_pi *data, va_list args);
void			printstring(t_pi *data, va_list args);
void			printpercent(t_pi *data);
int				numlen(long long int n, int base);
void			ft_putnbr(long long int n, int pow, int base, t_pi *data);
void			managediffs(int *diffs, int len, t_pi *data, long long int num);
void			printnumber(t_pi *data, va_list args, int base);
void			manageflags(t_pi *data, const char **format);
void			managewidth(t_pi *data, const char **format, va_list args);
void			manageprecision(t_pi *data, const char **format, va_list args);
void			managespecification(t_pi *data, const char **format);
int				isin(char c, char *str);
int				ft_printf(const char *format, ...);
#endif
