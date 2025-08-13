/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:33:10 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/03 12:42:04 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t	s_intlen(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	s_swap(char *conv)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	temp;

	len = ft_strlen(conv);
	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = conv[i];
		conv[i] = conv[j];
		conv[j] = temp;
		i++;
		j--;
	}
}

static int	s_sign(int n)
{
	if (n < 0)
	{
		n *= -1;
		return (1);
	}
	return (0);
}

static char	*s_build_conv(char *conv, int n, int i, int sign)
{
	while (n != 0)
	{
		conv[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (sign == 1)
	{
		conv[i] = '-';
		i++;
	}
	conv[i] = '\0';
	return (conv);
}

char	*ft_itoa(int n)
{
	char	*conv;
	int		i;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	conv = malloc((s_intlen(n) + 1) * sizeof(char));
	if (conv == NULL)
		return (NULL);
	sign = s_sign(n);
	if (sign == 1)
		n *= -1;
	i = 0;
	if (n == 0)
	{
		conv[i] = '0';
		i++;
	}
	s_build_conv(conv, n, i, sign);
	s_swap(conv);
	return (conv);
}
/*
int main() {
    int test_cases[] = {0, +123, -456, 7890, -98765, -2147483648};
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_cases; i++) {
        int n = test_cases[i];
        char *result = ft_itoa(n);

        // Sprawdzenie, czy wynik jest poprawny
        char expected[25];  // Zakładamy maksymalną długość wyniku
        sprintf(expected, "%d", n);

        if (strcmp(result, expected) == 0) {
            printf("Test dla %d: Prawidłowy wynik: %s\n", n, result);
        } else {
            printf("Test dla %d: 
			Błąd! Oczekiwano: %s, Otrzymano: %s\n", n, expected, result);
        }

        // Zwolnienie pamięci
        //free(result);
    }

    return 0;
}
*/
