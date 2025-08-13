/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_exec_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_redirections(t_exec **exec, t_parse *parsing, int *i)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(parsing->tokens[*i]->proc_text, ">") == 0)
		fd = open(parsing->tokens[++(*i)]->proc_text,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(parsing->tokens[*i]->proc_text, ">>") == 0)
		fd = open(parsing->tokens[++(*i)]->proc_text,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(parsing->tokens[*i]->proc_text, "<") == 0)
		fd = open(parsing->tokens[++(*i)]->proc_text, O_RDONLY);
	else if (ft_strcmp(parsing->tokens[*i]->proc_text, "<<") == 0)
	{
		fd = handle_heredoc(parsing->tokens[++(*i)]->proc_text);
		if (fd == -1)
		{
			perror("heredoc");
			return (-1);
		}
		(*exec)->in = fd;
	}
	return (fd);
}

static void	set_operator(t_exec **exec, t_parse *parsing, int *i)
{
	if ((*exec)->operator)
	{
		free((*exec)->operator);
		(*exec)->operator = NULL;
	}
	(*exec)->operator = ft_strdup(parsing->tokens[*i]->proc_text);
	(*exec)->token = OPERATOR;
}

static void	set_redirection_fd(t_exec **exec, t_parse *parsing, int *i, int fd)
{
	if (ft_strcmp(parsing->tokens[*i - 1]->proc_text, "<") == 0
		|| ft_strcmp(parsing->tokens[*i - 1]->proc_text, "<<") == 0)
		(*exec)->in = fd;
	else
		(*exec)->out = fd;
}

static void	create_new_node(t_exec **exec)
{
	t_exec	*new_node;

	new_node = alloc_exec();
	new_node->prev = *exec;
	(*exec)->next = new_node;
	*exec = new_node;
	(*exec)->next = NULL;
}

void	handle_operator(t_exec **exec, t_parse *parsing, int *i)
{
	int	fd;

	fd = handle_redirections(exec, parsing, i);
	if (fd == -1 && !is_redirection_operator(parsing->tokens[*i]->proc_text))
	{
		set_operator(exec, parsing, i);
		create_new_node(exec);
	}
	else if (fd != -1)
		set_redirection_fd(exec, parsing, i, fd);
}
