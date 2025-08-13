/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_too_many_args(void)
{
	write(STDERR_FILENO, "exit: too many arguments\n", 25);
	g_exit_code = 1;
}

static int	check_exit_arg_count(t_exec *exec)
{
	if (exec->args[0] && ft_strncmp(exec->args[0], "exit", 4) == 0
		&& exec->args[2])
	{
		handle_too_many_args();
		return (-1);
	}
	else if (!(exec->args[0] && ft_strncmp(exec->args[0], "exit", 4) == 0)
		&& exec->args[1])
	{
		handle_too_many_args();
		return (-1);
	}
	return (0);
}

int	validate_exit_args(t_exec *exec, t_data *data)
{
	char	*first_arg;

	if (exec->args[0] && ft_strncmp(exec->args[0], "exit", 4) == 0)
		first_arg = exec->args[1];
	else
		first_arg = exec->args[0];
	if (!first_arg)
	{
		exit_clear(data);
		exit(g_exit_code);
	}
	return (check_exit_arg_count(exec));
}
