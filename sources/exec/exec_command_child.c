/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:00 by wbardzin          #+#    #+#             */
/*   Updated: 2025/08/19 12:14:00 by wbardzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* execute_command_child:
*	Child process tries to execute the given command by setting
*	its input/output fds and searching for an executable.
*	Searching for executable in this order:
*		1. Execute builtin command
*		2. Execute system binaries for command.
*		3. Execute given command name directly (local bin)
*	If it cannot find a matching builtin or executable,
*	prints an error message.
*	Child exits with its executed program's exit code, or 1 if
*	it could not find one.
*/
void	execute_command_child(t_data *data, t_exec *exec)
{
	if (!exec || !exec->cmd)
	{
		printf("parsing error: no command to execute!\n");
		exit(EXIT_FAILURE);
	}
	if (apply_redirections(exec) == -1)
		exit(EXIT_FAILURE);
	set_pipe_fds(data->exec, exec);
	if (redirect_io(exec->in, exec->out) == -1)
		exit(EXIT_FAILURE);
	close_pipe_fds(data->exec, NULL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (is_builtin_command(exec->cmd))
	{
		execute_builtin(data, exec);
		exit(g_exit_code);
	}
	if (exec->cmd[0] != '/' && exec->cmd[0] != '.')
		handle_execve_path(data, exec);
	handle_execve_direct(exec);
	printf("minishell: %s: command not found\n", exec->cmd);
	exit(127);
}
