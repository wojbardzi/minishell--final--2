/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/18 21:50:39 by wbardzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_command_not_found(t_data *data, t_exec *command_struct)
{
	if (command_struct->cmd && command_struct->cmd[0])
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, command_struct->cmd,
			ft_strlen(command_struct->cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	else
	{
		write(STDERR_FILENO, "minishell: command not found\n", 28);
	}
	exit_clear(data);
	exit(127);
}

	//extern char	**environ;
static void	execute_command_with_path(char *command_path,
	t_exec *command_struct)
{
	if (command_struct->cmd && ft_strncmp(command_struct->cmd, "ls", 2) == 0
		&& !command_struct->cmd[2])
	{
		execve(command_path, command_struct->args, command_struct->envp);
	}
	else
	{
		execve(command_path, command_struct->args, command_struct->envp);
	}
	perror("execve");
	free(command_path);
	exit(EXIT_FAILURE);
}

int	handle_execve_path(t_data *data, t_exec *command_struct)
{
	char	*command_path;

	command_path = find_path(command_struct->cmd);
	if (!command_path)
		handle_command_not_found(data, command_struct);
	execute_command_with_path(command_path, command_struct);
	return (EXIT_FAILURE);
}

void	handle_execve_direct(t_exec *command_struct)
{
	execve(command_struct->cmd, command_struct->args, command_struct->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}
