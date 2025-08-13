/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_input_redirection(t_redirection *current)
{
	int	test_fd;

	test_fd = open(current->filename, O_RDONLY);
	if (test_fd == -1)
	{
		perror(current->filename);
		return (-1);
	}
	close(test_fd);
	return (0);
}

static int	validate_output_redirection(t_redirection *current)
{
	int	test_fd;

	test_fd = open(current->filename, O_WRONLY | O_CREAT, 0644);
	if (test_fd == -1)
	{
		perror(current->filename);
		return (-1);
	}
	close(test_fd);
	return (0);
}

int	validate_redirections(t_exec *exec)
{
	t_redirection	*current;

	current = exec->redirections;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (validate_input_redirection(current) == -1)
				return (-1);
		}
		else if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
		{
			if (validate_output_redirection(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
