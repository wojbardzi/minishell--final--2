/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirection	*create_redirection(t_redir_type type, char *filename)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

int	add_redirection(t_exec *exec, t_redir_type type, char *filename)
{
	t_redirection	*new_redir;
	t_redirection	*current;

	new_redir = create_redirection(type, filename);
	if (!new_redir)
		return (-1);
	if (!exec->redirections)
	{
		exec->redirections = new_redir;
	}
	else
	{
		current = exec->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (0);
}

t_redir_type	get_redirection_type(char *op)
{
	if (ft_strcmp(op, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(op, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(op, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(op, "<<") == 0)
		return (REDIR_HEREDOC);
	return (-1);
}

int	handle_redirection_token(t_parse *parsing, t_exec *exec,
								int *i, int end)
{
	if (*i + 1 >= end || !parsing->tokens[*i + 1])
	{
		printf("minishell: syntax error near "
			"unexpected token `newline'\n");
		return (-1);
	}
	if (add_redirection(exec,
			get_redirection_type(parsing->tokens[*i]->proc_text),
			parsing->tokens[*i + 1]->proc_text) == -1)
		return (-1);
	*i += 2;
	return (0);
}

void	cleanup_redirections(t_redirection *redirections)
{
	t_redirection	*current;
	t_redirection	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		if (current->fd != -1)
			close(current->fd);
		free(current);
		current = next;
	}
}
