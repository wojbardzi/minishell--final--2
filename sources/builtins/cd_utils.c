/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:41:08 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/18 16:12:35 by wbardzin         ###   ########.fr       */
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

static int	count_args_in_string(char *s)
{
	int	j;
	int	arg_count;

	j = 0;
	arg_count = 0;
	while (s[j])
	{
		while (s[j] && ft_isspace(s[j]))
			j++;
		if (s[j])
		{
			arg_count++;
			while (s[j] && !ft_isspace(s[j]))
				j++;
		}
	}
	return (arg_count);
}

int	is_correct(t_exec *exec)
{
	int	i;
	int	arg_start;
	int	total_args;

	if (!exec || !exec->args)
		return (0);
	arg_start = 0;
	if (exec->args[0] && ft_strncmp(exec->args[0], "cd", 2) == 0)
		arg_start = 1;
	i = arg_start;
	total_args = 0;
	while (exec->args[i])
	{
		total_args += count_args_in_string(exec->args[i]);
		if (total_args > 1)
		{
			write(STDERR_FILENO, "cd: too many arguments\n", 23);
			return (1);
		}
		i++;
	}
	return (0);
}
