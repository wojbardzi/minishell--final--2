/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:02:36 by wojti             #+#    #+#             */
/*   Updated: 2025/08/13 13:02:41 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_pipeline_command(t_data *data, t_exec *current,
		int *prev_fd, int pipe_fd[2])
{
	pid_t	last_pid;

	if (current->next)
	{
		if (setup_pipe(current, pipe_fd) == -1)
			return (-1);
	}
	last_pid = execute_command(data, current);
	close_fds(*prev_fd, current->out);
	*prev_fd = current->in;
	return (last_pid);
}

static int	wait_for_children(pid_t *pids, int pid_count, int *status,
	pid_t last_pid)
{
	pid_t	wait_pid;
	int		temp_status;
	int		waited_count;
	int		max_iterations;
	int		iteration_count;

	waited_count = 0;
	max_iterations = 1000000;
	iteration_count = 0;
	while (waited_count < pid_count && iteration_count < max_iterations)
	{
		wait_pid = waitpid(-1, &temp_status, WNOHANG);
		if (wait_pid > 0)
		{
			waited_count++;
			if (wait_pid == last_pid)
				*status = temp_status;
		}
		iteration_count++;
	}
	if (iteration_count >= max_iterations)
		kill_all_processes(pids, pid_count);
	return (0);
}

static int	pipeline_loop_body(t_data *data,
		pid_t *pids, int *pid_count, int max_pids)
{
	int		pipe_fd[2];
	pid_t	last_pid;
	int		prev_fd;
	t_exec	*current;

	last_pid = -1;
	current = data->exec;
	prev_fd = STDIN_FILENO;
	while (current)
	{
		last_pid = handle_pipeline_command(data, current, &prev_fd, pipe_fd);
		if (last_pid == -1)
		{
			free(pids);
			data->pids = NULL;
			return (-1);
		}
		if (last_pid != -1 && *pid_count < max_pids)
			pids[(*pid_count)++] = last_pid;
		current = current->next;
	}
	return (last_pid);
}

static int	execute_pipeline_commands(t_data *data, int *status,
	pid_t *pids, int *pid_count)
{
	int		max_pids;
	pid_t	last_pid;

	max_pids = 10;
	last_pid = pipeline_loop_body(data, pids, pid_count, max_pids);
	if (last_pid == -1)
		return (-1);
	wait_for_children(pids, *pid_count, status, last_pid);
	free(pids);
	data->pids = NULL;
	return (0);
}

int	pipeline_loop(t_data *data, int *status)
{
	pid_t	*pids;
	int		max_pids;
	int		pid_count;
	t_exec	*current;

	pid_count = 0;
	if (init_pipeline_vars(data, &pids, &max_pids) == -1)
		return (-1);
	current = data->exec;
	if (is_single_builtin_check(current))
	{
		*status = execute_command(data, current) << 8;
		return (0);
	}
	return (execute_pipeline_commands(data, status, pids, &pid_count));
}
