/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:40:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char delim)
{
	static char	*static_str;
	char		*token;

	if (str)
		static_str = str;
	if (!static_str)
		return (NULL);
	token = static_str;
	while (*static_str && *static_str != delim)
		static_str++;
	if (*static_str == delim)
	{
		*static_str = '\0';
		static_str++;
	}
	else
		static_str = NULL;
	if (*token)
		return (token);
	return (NULL);
}
