/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipeline_vars(t_data *data, pid_t **pids, int *max_pids)
{
	*max_pids = 10;
	*pids = malloc(*max_pids * sizeof(pid_t));
	if (!*pids)
		return (-1);
	data->pids = *pids;
	return (0);
}

int	is_single_builtin_check(t_exec *current)
{
	return (is_builtin_command(current->cmd) && !current->next
		&& !current->prev);
}

void	kill_all_processes(pid_t *pids, int pid_count)
{
	int	i;

	i = 0;
	while (i < pid_count)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}
