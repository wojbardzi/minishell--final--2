/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:30:11 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	char	*builtin_commands[8];
	int		i;

	builtin_commands[0] = "echo";
	builtin_commands[1] = "cd";
	builtin_commands[2] = "pwd";
	builtin_commands[3] = "export";
	builtin_commands[4] = "unset";
	builtin_commands[5] = "env";
	builtin_commands[6] = "exit";
	builtin_commands[7] = NULL;
	i = 0;
	while (builtin_commands[i])
	{
		if (cmd && ft_strncmp(cmd, builtin_commands[i],
				ft_strlen(builtin_commands[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	exec_builtin_parent(t_data *data, t_exec *command_struct)
{
	int	saved_stdin;
	int	saved_stdout;

	save_stdio(&saved_stdin, &saved_stdout);
	if (apply_redirections(command_struct) == -1)
	{
		restore_stdio(saved_stdin, saved_stdout);
		return (g_exit_code);
	}
	if (redirect_io(command_struct->in, command_struct->out) == -1)
	{
		restore_stdio(saved_stdin, saved_stdout);
		return (1);
	}
	execute_builtin(data, command_struct);
	restore_stdio(saved_stdin, saved_stdout);
	return (g_exit_code);
}

static int	exec_child(t_data *data, t_exec *command_struct, int is_builtin)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (apply_redirections(command_struct) == -1)
		exit(g_exit_code);
	if (redirect_io(command_struct->in, command_struct->out) == -1)
		exit(EXIT_FAILURE);
	if (is_builtin)
	{
		execute_builtin(data, command_struct);
		exit(g_exit_code);
	}
	if (!command_struct->cmd)
		exit(EXIT_FAILURE);
	if (command_struct->cmd[0] != '/' && command_struct->cmd[0] != '.')
		handle_execve_path(data, command_struct);
	handle_execve_direct(command_struct);
	return (0);
}

int	execute_command(t_data *data, t_exec *command_struct)
{
	pid_t	pid;
	int		is_builtin;
	int		is_pipeline;

	is_pipeline = (command_struct->prev != NULL
			|| command_struct->next != NULL);
	is_builtin = is_builtin_command(command_struct->cmd);
	if (is_builtin && !is_pipeline)
		return (exec_builtin_parent(data, command_struct));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
		exec_child(data, command_struct, is_builtin);
	return (pid);
}

int	execute_pipeline(t_data *data)
{
	int	status;

	status = 0;
	if (pipeline_loop(data, &status) == -1)
		return (-1);
	unlink("heredoc_tmp");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
