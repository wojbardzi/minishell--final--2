/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file_ops.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_input_redirection(t_redirection *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		return (-1);
	}
	return (0);
}

static int	open_output_redirection(t_redirection *redir)
{
	redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		return (-1);
	}
	return (0);
}

static int	open_append_redirection(t_redirection *redir)
{
	redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		return (-1);
	}
	return (0);
}

static int	open_heredoc_redirection(t_redirection *redir)
{
	redir->fd = handle_heredoc(redir->filename);
	if (redir->fd == -1)
	{
		perror("heredoc");
		return (-1);
	}
	return (0);
}

int	open_redirection_file(t_redirection *redir)
{
	if (redir->type == REDIR_IN)
		return (open_input_redirection(redir));
	else if (redir->type == REDIR_OUT)
		return (open_output_redirection(redir));
	else if (redir->type == REDIR_APPEND)
		return (open_append_redirection(redir));
	else if (redir->type == REDIR_HEREDOC)
		return (open_heredoc_redirection(redir));
	return (-1);
}
