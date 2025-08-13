/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:23:57 by zuraw             #+#    #+#             */
/*   Updated: 2025/07/27 13:31:59 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(t_exec *exec, t_data *data)
{
	char	*target_path;
	char	*current_path;
	char	*temp_path;
	char	*resolved_path;

	if (is_correct(exec) == 1)
		return (1);
	current_path = get_current_path();
	target_path = determine_target_path(exec, data);
	if (target_path == NULL)
		return (free(current_path), 1);
	temp_path = ft_strdup(target_path);
	if (!temp_path)
	{
		perror("malloc");
		free(current_path);
		return (1);
	}
	if (change_dir(temp_path) == 1)
		return (free(current_path), 1);
	resolved_path = get_current_path();
	cd_change_envp(resolved_path, current_path, data);
	free(current_path);
	free(temp_path);
	return (free(resolved_path), 0);
}
