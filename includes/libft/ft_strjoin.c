/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:32:48 by pzurawic          #+#    #+#             */
/*   Updated: 2024/03/01 12:12:46 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = malloc(lens1 + lens2 + 1);
	if (str == NULL)
		return (NULL);
	if (lens1 > 0)
		ft_strlcpy(str, s1, lens1 + 1);
	if (lens2 > 0)
		ft_strlcpy(str + lens1, s2, lens2 + 1);
	str[lens1 + lens2] = '\0';
	return (str);
}
