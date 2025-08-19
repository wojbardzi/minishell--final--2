/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:00:00 by wbardzin          #+#    #+#             */
/*   Updated: 2025/08/19 12:14:02 by wbardzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* close_pipe_fds:
*	Closes the pipe fds of all commands. A pointer to a command to skip
*	can be specified to skip closing that command's pipe fds:
*		- The parent will specify NULL for the skip command while closing
*		all pipe fds.
*		- The child will specify its own command as skip command while
*		closing all pipe fds so as to not accidentally close its own
*		pipe fds.
*/
void	close_pipe_fds(t_exec *exec, t_exec *skip_cmd)
{
	while (exec)
	{
		if (exec != skip_cmd && exec->pipe_fd)
		{
			close(exec->pipe_fd[0]);
			close(exec->pipe_fd[1]);
		}
		exec = exec->next;
	}
}

/* create_pipes:
*	Creates a set of pipes for each piped command in the list
*	of commands.
*	Returns true if successful, false in case of failure.
*/
bool	create_pipes(t_data *data)
{
	int		*fd;
	t_exec	*tmp;

	tmp = data->exec;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof(int) * 2);
			if (!fd || pipe(fd) != 0)
			{
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

/* set_pipe_fds:
*	Sets the pipe fds for this command. If the previous command
*	was piped to this one, sets the input as the read end of
*	the previous command. If this command is piped to the
*	next, sets the output as the write end of the pipe.
*		pipe_fd[0] = read end of pipe.
*		pipe_fd[1] = write end of pipe.
*	Returns true when the pipe file descriptors are set.
*/
bool	set_pipe_fds(t_exec *exec, t_exec *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(exec, c);
	return (true);
}
