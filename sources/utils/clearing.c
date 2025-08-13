/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:47:10 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 19:35:52 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_parsing(t_parse *parsing)
{
	if (parsing->operators)
	{
		free(parsing->operators);
		parsing->operators = NULL;
	}
	if (parsing->words)
	{
		free_words(parsing);
		parsing->words = NULL;
	}
	if (parsing->tokens)
	{
		free_tokens(parsing);
		parsing->tokens = NULL;
	}
	if (parsing->input)
	{
		free(parsing->input);
		parsing->input = NULL;
		parsing->input_items = 0;
	}
}

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

static void	free_exec_fields(t_exec *exec)
{
	if (exec->operator)
	{
		free(exec->operator);
		exec->operator = NULL;
	}
	if (exec->args)
	{
		free_args(exec->args);
		exec->args = NULL;
	}
	if (exec->cmd)
	{
		free(exec->cmd);
		exec->cmd = NULL;
	}
	if (exec->redirections)
	{
		cleanup_redirections(exec->redirections);
		exec->redirections = NULL;
	}
}

void	clear_exec(t_exec *exec)
{
	t_exec	*temp;

	if (!exec)
		return ;
	while (exec->prev != NULL)
		exec = exec->prev;
	while (exec)
	{
		temp = exec->next;
		free_exec_fields(exec);
		free(exec);
		exec = temp;
	}
}
