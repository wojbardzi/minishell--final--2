/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:31:36 by zuraw             #+#    #+#             */
/*   Updated: 2025/07/27 13:31:59 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data_envp(t_data *data)
{
	int	i;

	if (!data || !data->envp)
		return ;
	i = 0;
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
}
