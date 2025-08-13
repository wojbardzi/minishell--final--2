/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:11:23 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/13 13:00:52 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_operators(char *operators)
{
	operators[0] = '&';
	operators[1] = '|';
	operators[2] = '>';
	operators[3] = '<';
}

bool	look_for_operator(char c)
{
	int		i;
	char	operators[4];

	set_operators(operators);
	i = -1;
	while (operators[++i])
	{
		if (operators[i] == c)
			return (true);
	}
	return (false);
}
