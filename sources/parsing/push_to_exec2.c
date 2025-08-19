/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbardzin <wbardzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:02:13 by wojti             #+#    #+#             */
/*   Updated: 2025/08/19 12:14:03 by wbardzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_pipe_operator(char *op)
{
	return (ft_strcmp(op, "|") == 0);
}

static int	handle_pipe_operator(t_parse *parsing, t_exec **current, int *i)
{
	if (parsing->tokens[*i]
		&& parsing->tokens[*i]->type == OPERATOR
		&& is_pipe_operator(parsing->tokens[*i]->proc_text))
	{
		(*current)->operator = ft_strdup(parsing->tokens[*i]->proc_text);
		(*current)->pipe_output = true;
		(*current)->next = alloc_exec();
		if (!(*current)->next)
		{
			g_exit_code = 1;
			return (-1);
		}
		(*current)->next->prev = *current;
		*current = (*current)->next;
		(*i)++;
		return (1);
	}
	return (0);
}

static void	check_operator_end(t_exec *current)
{
	if (current->prev && current->prev->operator && !current->cmd)
	{
		printf("Instruction cannot ends with OPERATOR\n");
		g_exit_code = 2;
	}
}

void	push_to_exec(t_parse *parsing, t_exec *exec)
{
	int		i;
	t_exec	*current;
	int		result;

	i = 0;
	current = exec;
	while (parsing->tokens[i])
	{
		if (parse_command_with_redirections(parsing, current, &i) == -1)
		{
			g_exit_code = 1;
			return ;
		}
		result = handle_pipe_operator(parsing, &current, &i);
		if (result == -1)
			return ;
		if (result == 0)
			break ;
	}
	check_operator_end(current);
}
