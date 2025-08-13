/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_exec_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/02 12:00:00 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_args_array(t_exec *exec, int arg_count)
{
	exec->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!exec->args)
		return (1);
	exec->args[arg_count] = NULL;
	return (0);
}

void	cleanup_on_error(t_exec *exec, int fail_idx)
{
	int	k;

	if (fail_idx > 0)
	{
		k = 0;
		while (k < fail_idx)
		{
			if (exec->args[k] && k > 0)
				free(exec->args[k]);
			k++;
		}
	}
	if (exec->cmd)
		free(exec->cmd);
	if (exec->args)
		free(exec->args);
}

int	is_redirection_operator(char *op)
{
	return (ft_strcmp(op, ">") == 0 || ft_strcmp(op, ">>") == 0
		|| ft_strcmp(op, "<") == 0 || ft_strcmp(op, "<<") == 0);
}
