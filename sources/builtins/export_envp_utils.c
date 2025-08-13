/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:45:00 by zuraw             #+#    #+#             */
/*   Updated: 2025/07/27 13:31:59 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_existing_envp(char **envp, char **new_envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			error_exit();
		i++;
	}
}

static void	add_new_env_entry(char **new_envp, char *arg, int index)
{
	new_envp[index] = prepare_envp_entry(arg);
	if (!new_envp[index])
		error_exit();
}

void	create_and_update_envp(t_data *data, char *arg)
{
	char	**new_envp;
	int		i;

	new_envp = create_new_envp(data->envp);
	if (!new_envp)
		return ;
	copy_existing_envp(data->envp, new_envp);
	i = 0;
	while (data->envp[i])
		i++;
	add_new_env_entry(new_envp, arg, i);
	free_data_envp(data);
	data->envp = new_envp;
	set_exec_envp(data->exec, data->envp);
}
