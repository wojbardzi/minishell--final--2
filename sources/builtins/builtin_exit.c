/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_exit_error(char *arg, t_data *data)
{
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	exit_clear(data);
	exit(2);
}

static char	*get_first_exit_arg(t_exec *exec)
{
	char	*first_arg;

	if (exec->args[0] && ft_strncmp(exec->args[0], "exit", 4) == 0)
		first_arg = exec->args[1];
	else
		first_arg = exec->args[0];
	return (first_arg);
}

void	builtin_exit(t_exec *exec, t_data *data)
{
	int		exit_code;
	long	num;
	char	*endptr;
	char	*first_arg;

	printf("exit\n");
	if (!exec || !exec->args)
	{
		exit_clear(data);
		exit(g_exit_code);
	}
	if (validate_exit_args(exec, data) == -1)
		return ;
	first_arg = get_first_exit_arg(exec);
	num = strtol(first_arg, &endptr, 10);
	if (*endptr != '\0')
		handle_exit_error(first_arg, data);
	exit_code = (int)(num % 256);
	if (exit_code < 0)
		exit_code += 256;
	exit_clear(data);
	exit(exit_code);
}
