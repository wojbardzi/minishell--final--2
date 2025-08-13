/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 22:12:45 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr(int n)
{
	int		count;
	char	*str;

	str = ft_itoa(n);
	if (!str)
		return (0);
	count = ft_print_str(str);
	free(str);
	return (count);
}

int	ft_print_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_unsigned(n / 10);
	count += ft_print_char((n % 10) + '0');
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int					count;
	unsigned long long	addr;

	count = 0;
	if (!ptr)
		return (ft_print_str("(nil)"));
	addr = (unsigned long long)ptr;
	count += ft_print_str("0x");
	count += ft_print_hex_long(addr, 0);
	return (count);
}

int	ft_print_hex_long(unsigned long long n, int uppercase)
{
	int		count;
	char	*hex_digits;

	count = 0;
	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n >= 16)
		count += ft_print_hex_long(n / 16, uppercase);
	count += ft_print_char(hex_digits[n % 16]);
	return (count);
}
