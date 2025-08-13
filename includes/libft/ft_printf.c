/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 22:12:45 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	return (count);
}

static int	ft_print_hex(unsigned int n, int uppercase)
{
	int		count;
	char	*hex_digits;

	count = 0;
	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n >= 16)
		count += ft_print_hex(n / 16, uppercase);
	count += ft_print_char(hex_digits[n % 16]);
	return (count);
}

static int	ft_handle_format(const char *format, va_list args)
{
	if (*format == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (*format == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (*format == 'd' || *format == 'i')
		return (ft_print_nbr(va_arg(args, int)));
	else if (*format == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (*format == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (*format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (*format == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (*format == '%')
		return (ft_print_char('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				count += ft_handle_format(format, args);
		}
		else
			count += ft_print_char(*format);
		format++;
	}
	va_end(args);
	return (count);
}
