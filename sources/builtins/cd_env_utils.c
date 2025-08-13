/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:25:00 by zuraw             #+#    #+#             */
/*   Updated: 2025/07/27 13:31:59 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**add_env_var(t_data *data, const char *key, const char *value)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (data->envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (perror("malloc"), NULL);
	i = 0;
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		if (!new_envp[i])
			return (free_double_array(new_envp), NULL);
		i++;
	}
	new_envp[i] = ft_strjoin(key, value);
	if (!new_envp[i])
		return (free_double_array(new_envp), NULL);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

int	update_env_var(t_data *data, char *key, char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0)
		{
			free(data->envp[i]);
			new_value = ft_strjoin(key, value);
			if (!new_value)
				return (0);
			data->envp[i] = new_value;
			return (1);
		}
		i++;
	}
	return (0);
}

void	cd_change_envp(char *new_pwd, char *old_pwd, t_data *data)
{
	char	**temp_envp;

	if (!update_env_var(data, "PWD=", new_pwd))
	{
		temp_envp = add_env_var(data, "PWD=", new_pwd);
		if (temp_envp)
		{
			free_double_array(data->envp);
			data->envp = temp_envp;
		}
	}
	if (!update_env_var(data, "OLDPWD=", old_pwd))
	{
		temp_envp = add_env_var(data, "OLDPWD=", old_pwd);
		if (temp_envp)
		{
			free_double_array(data->envp);
			data->envp = temp_envp;
		}
	}
	set_exec_envp(data->exec, data->envp);
}
