/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:54:56 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_redirections(t_parse *parsing, t_exec *exec,
									int start, int end)
{
	int	i;

	i = start;
	while (i < end && parsing->tokens[i])
	{
		if (parsing->tokens[i]->type == OPERATOR
			&& is_redirection_operator(parsing->tokens[i]->proc_text))
		{
			if (handle_redirection_token(parsing, exec, &i, end) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

static int	collect_args_and_redirections(t_parse *parsing, t_exec *exec,
										int start, int end)
{
	char	**args;
	int		arg_count;
	int		arg_idx;

	arg_count = count_args(parsing, start, end);
	if (arg_count == -1)
		return (-1);
	if (process_redirections(parsing, exec, start, end) == -1)
		return (-1);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (-1);
	arg_idx = fill_args_array(parsing, args, start, end);
	if (arg_idx == -1)
	{
		free(args);
		return (-1);
	}
	args[arg_idx] = NULL;
	return (setup_exec_cmd(exec, args, arg_count));
}

static int	find_command_boundary(t_parse *parsing, int start)
{
	int	i;

	i = start;
	while (i < parsing->input_items && parsing->tokens[i])
	{
		if (parsing->tokens[i]->type == OPERATOR)
		{
			if (!is_redirection_operator(parsing->tokens[i]->proc_text))
				break ;
			else if (i + 1 < parsing->input_items && parsing->tokens[i + 1])
				i += 2;
			else
				break ;
		}
		else
			i++;
	}
	return (i);
}

int	parse_command_with_redirections(t_parse *parsing, t_exec *exec, int *index)
{
	int	end;

	if (!parsing->tokens[*index])
		return (-1);
	end = find_command_boundary(parsing, *index);
	if (collect_args_and_redirections(parsing, exec, *index, end) == -1)
		return (-1);
	if (parsing->tokens[*index])
		exec->envp = parsing->tokens[*index]->envp;
	*index = end;
	return (0);
}
