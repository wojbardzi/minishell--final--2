/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:24:39 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_unset_args(t_exec *exec)
{
	if (exec->args[0] && ft_strncmp(exec->args[0], "unset", 5) == 0)
	{
		if (!exec->args[1])
			return (NULL);
		return (exec->args + 1);
	}
	else
	{
		if (!exec->args[0])
			return (NULL);
		return (exec->args);
	}
}

int	builtin_unset(t_exec *exec, t_data *data)
{
	int		count;
	char	**new_envp;
	char	**args_to_unset;

	if (!exec || !exec->args || !data || !data->envp)
		return (0);
	args_to_unset = get_unset_args(exec);
	if (!args_to_unset)
		return (0);
	count = count_args_in_envp(data->envp, args_to_unset);
	new_envp = allocate_new_envp(data->envp, count);
	if (!new_envp)
		return (1);
	new_envp = build_new_envp(data->envp, new_envp, args_to_unset);
	if (!new_envp)
		return (1);
	free_data_envp(data);
	data->envp = new_envp;
	set_exec_envp(data->exec, data->envp);
	return (0);
}
