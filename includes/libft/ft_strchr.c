/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzurawic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:44:51 by pzurawic          #+#    #+#             */
/*   Updated: 2024/02/28 20:05:59 by pzurawic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*firstc;

	firstc = (char *)s;
	if (c == '\0')
	{
		firstc += ft_strlen(firstc);
		return (firstc);
	}
	while (*firstc != '\0')
	{
		if ((unsigned char)*firstc == (unsigned char)c)
			return (firstc);
		firstc++;
	}
	return (NULL);
}
