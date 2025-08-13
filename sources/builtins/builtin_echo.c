/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_echo_flag(char **args, int *i)
{
	int	n_flag;

	n_flag = 0;
	if (args[*i] && ft_strncmp(args[*i], "-n", 3) == 0)
	{
		n_flag = 1;
		(*i)++;
	}
	return (n_flag);
}

static void	print_echo_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

int	builtin_echo(t_exec *exec)
{
	int	i;
	int	n_flag;

	if (!exec || !exec->args)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	i = 0;
	if (exec->args[0] && ft_strncmp(exec->args[0], "echo", 4) == 0)
		i = 1;
	n_flag = check_echo_flag(exec->args, &i);
	print_echo_args(exec->args, i);
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
