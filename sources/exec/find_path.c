/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:02:55 by wojti             #+#    #+#             */
/*   Updated: 2025/08/18 14:44:24 by wbardzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	build_exec_path(char *dst, char *dir, const char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (dir[i])
	{
		dst[i] = dir[i];
		i++;
	}
	dst[i++] = '/';
	j = 0;
	while (cmd[j])
		dst[i++] = cmd[j++];
	dst[i] = '\0';
}

char	*find_path(const char *cmd)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	exec_path[4242];

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path = ft_strdup(path_env);
	if (!path)
		return (NULL);
	dir = ft_strtok(path, ':');
	while (dir)
	{
		build_exec_path(exec_path, dir, cmd);
		if (access(exec_path, X_OK) == 0)
		{
			free(path);
			return (ft_strdup(exec_path));
		}
		dir = ft_strtok(NULL, ':');
	}
	free(path);
	return (NULL);
}
