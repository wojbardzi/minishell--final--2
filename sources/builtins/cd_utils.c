/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:41:08 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 19:35:56 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_dir(char *temp_path)
{
	if (chdir(temp_path) == -1)
	{
		perror("cd");
		free(temp_path);
		return (1);
	}
	return (0);
}

int	is_correct(t_exec *exec)
{
	int	i;
	int	arg_start;
	int	arg_count;

	if (!exec || !exec->args)
		return (0);
	arg_start = 0;
	if (exec->args[0] && ft_strncmp(exec->args[0], "cd", 2) == 0)
		arg_start = 1;
	i = arg_start;
	while (exec->args[i])
		i++;
	arg_count = i - arg_start;
	if (arg_count > 1)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	return (0);
}
