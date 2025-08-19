/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:00 by wbardzin          #+#    #+#             */
/*   Updated: 2025/08/19 12:16:13 by wbardzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

/* get_children:
*	Waits for children to terminate after cleaning up fds and commands.
*	Returns a child's exit status as bash does:
*		"The return status of a simple command is its exit status as 
*		provided by the POSIX 1003.1 waitpid function, or 128+n if 
*		the command was terminated by signal n."
*	If there are multiple commands in a pipeline:
*		"The exit status of a pipeline is the exit status of the last 
*		command in the pipeline"
*/
static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_pipe_fds(data->exec, NULL);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid > 0)
			handle_child_status(status, wpid, data, &save_status);
		continue ;
	}
	return (calculate_exit_status(save_status));
}

/* create_children:
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the
*	main process (no children created in this case).
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.
*/
static int	create_children(t_data *data)
{
	t_exec	*exec;

	exec = data->exec;
	data->pids[0] = -1;
	while (data->pids[0] != 0 && exec)
	{
		data->pids[0] = fork();
		if (data->pids[0] == -1)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		else if (data->pids[0] == 0)
			execute_command_child(data, exec);
		exec = exec->next;
	}
	return (get_children(data));
}

/* prep_for_exec:
*	Prepares the command list for execution, creates pipes
*	and checks the input and output files.
*	Returns false in case of error, true if all is ready to
*	execute.
*/
static int	prep_for_exec(t_data *data)
{
	if (!data || !data->exec)
		return (EXIT_SUCCESS);
	if (!data->exec->cmd)
	{
		if (data->exec->redirections
			&& apply_redirections(data->exec) == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (127);
}

/* execute_pipeline_new:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate. This is the new implementation
*	based on the reference project.
*	Returns the exit code of the last child to terminate. Or
*	exit code 1 in case of failure in the child creation process.
*/
int	execute_pipeline_new(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != 127)
		return (ret);
	if (!data->exec->pipe_output && !data->exec->prev
		&& is_builtin_command(data->exec->cmd))
	{
		ret = exec_builtin_parent(data, data->exec);
		return (ret);
	}
	if (!data->pids)
	{
		data->pids = malloc(sizeof(pid_t) * 10);
		if (!data->pids)
			return (EXIT_FAILURE);
	}
	return (create_children(data));
}
