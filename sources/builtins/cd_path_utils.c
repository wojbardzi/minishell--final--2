/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:30:00 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*determine_target_path(t_exec *exec, t_data *data)
{
	char	*target_path;
	char	*first_arg;

	if (exec->args[0] && ft_strncmp(exec->args[0], "cd", 2) == 0)
		first_arg = exec->args[1];
	else
		first_arg = exec->args[0];
	if (!first_arg || ft_strncmp(first_arg, "~", 1) == 0)
	{
		target_path = get_env_value("HOME", data->envp);
		if (!target_path)
			return (NULL);
	}
	else if (first_arg && ft_strncmp(first_arg, "-", 1) == 0)
	{
		target_path = get_env_value("OLDPWD", data->envp);
		if (!target_path)
			return (NULL);
	}
	else
		target_path = first_arg;
	return (target_path);
}
