/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:02:47 by wojti             #+#    #+#             */
/*   Updated: 2025/08/13 13:02:49 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_output_redirection(t_exec *curr)
{
	t_redirection	*redir;

	redir = curr->redirections;
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static int	create_pipe_fds(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	setup_pipe(t_exec *curr, int *pipe_fd)
{
	int	has_output_redir;

	if (!curr || !curr->next)
		return (-1);
	if (create_pipe_fds(pipe_fd) == -1)
		return (-1);
	has_output_redir = has_output_redirection(curr);
	if (has_output_redir)
	{
		curr->next->in = pipe_fd[0];
		close(pipe_fd[1]);
	}
	else
	{
		curr->out = pipe_fd[1];
		curr->next->in = pipe_fd[0];
	}
	return (0);
}

int	redirect_io(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) == -1)
		{
			perror("dup2 (stdin)");
			return (-1);
		}
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
		{
			perror("dup2 (stdout)");
			return (-1);
		}
		close(out);
	}
	return (0);
}
