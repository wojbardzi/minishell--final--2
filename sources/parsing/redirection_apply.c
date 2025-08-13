/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_apply.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_input_redirection(t_exec *exec, t_redirection *current)
{
	if (exec->in != STDIN_FILENO)
		close(exec->in);
	exec->in = current->fd;
}

static void	handle_output_redirection(t_exec *exec, t_redirection *current)
{
	if (exec->out != STDOUT_FILENO)
		close(exec->out);
	exec->out = current->fd;
}

int	apply_redirections(t_exec *exec)
{
	t_redirection	*current;

	current = exec->redirections;
	while (current)
	{
		if (open_redirection_file(current) == -1)
		{
			g_exit_code = 1;
			return (-1);
		}
		if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
			handle_input_redirection(exec, current);
		else if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
			handle_output_redirection(exec, current);
		current = current->next;
	}
	return (0);
}
