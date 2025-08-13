/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:23:13 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_current_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	return (path);
}

int	builtin_pwd(void)
{
	char	*path;

	path = get_current_path();
	printf("%s\n", path);
	free(path);
	return (0);
}
