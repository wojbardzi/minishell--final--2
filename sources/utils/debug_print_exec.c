/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_exec_cmd(t_exec *current)
{
	if (current->cmd == NULL)
		printf("  CMD is NULL\n");
	else
		printf("  CMD: %s\n", current->cmd);
}

static void	print_exec_args(t_exec *current)
{
	int	i;

	if (current->args == NULL)
		printf("  Args are NULL\n");
	else
	{
		i = 0;
		while (current->args[i])
		{
			printf("  Arg[%d]: %s\n", i, current->args[i]);
			i++;
		}
	}
}

static void	print_exec_operator(t_exec *current)
{
	if (current->operator)
		printf("  Operator: %s\n", current->operator);
}

void	print_exec(t_exec *exec)
{
	int		node;
	t_exec	*current;

	node = 0;
	current = exec;
	printf("\nExec:\n");
	while (current)
	{
		printf("Node %d:\n", node);
		print_exec_cmd(current);
		print_exec_args(current);
		print_exec_operator(current);
		current = current->next;
		node++;
		if (current)
			printf("\n");
	}
	printf("***************************\n\n");
}
