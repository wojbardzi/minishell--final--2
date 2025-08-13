/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:17:05 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_export(t_exec *exec, t_data *data)
{
	int	i;

	if (!exec || !exec->args || !data)
		return (1);
	i = 0;
	if (exec->args[0] && ft_strncmp(exec->args[0], "export", 6) == 0)
		i = 1;
	if (!exec->args[i])
	{
		print_sorted_array(data->envp);
		return (0);
	}
	while (exec->args[i])
	{
		if (!is_valid(exec->args[i]))
		{
			write(STDERR_FILENO, "export: `", 9);
			write(STDERR_FILENO, exec->args[i], ft_strlen(exec->args[i]));
			write(STDERR_FILENO, "': not a valid identifier\n", 26);
			return (1);
		}
		update_envp(data, exec, &i);
	}
	set_exec_envp(data->exec, data->envp);
	return (0);
}
