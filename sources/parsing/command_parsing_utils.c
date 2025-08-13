/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redirection_syntax(t_parse *parsing, int i, int end)
{
	if (i + 1 >= end || !parsing->tokens[i + 1])
	{
		printf("minishell: syntax error near "
			"unexpected token `newline'\n");
		return (-1);
	}
	return (0);
}

int	count_args(t_parse *parsing, int start, int end)
{
	int	arg_count;
	int	i;

	arg_count = 0;
	i = start;
	while (i < end && parsing->tokens[i])
	{
		if (parsing->tokens[i]->type == OPERATOR)
		{
			if (is_redirection_operator(parsing->tokens[i]->proc_text))
			{
				if (check_redirection_syntax(parsing, i, end) == -1)
					return (-1);
				i += 2;
				continue ;
			}
		}
		else
			arg_count++;
		i++;
	}
	return (arg_count);
}

static int	process_token_in_args(char **args, t_parse *parsing,
							int *arg_idx, int i)
{
	args[*arg_idx] = ft_strdup(parsing->tokens[i]->proc_text);
	if (!args[*arg_idx])
	{
		while (--(*arg_idx) >= 0)
			free(args[*arg_idx]);
		return (-1);
	}
	(*arg_idx)++;
	return (0);
}

int	fill_args_array(t_parse *parsing, char **args, int start, int end)
{
	int	i;
	int	arg_idx;

	arg_idx = 0;
	i = start;
	while (i < end && parsing->tokens[i])
	{
		if (parsing->tokens[i]->type != OPERATOR)
		{
			if (process_token_in_args(args, parsing, &arg_idx, i) == -1)
				return (-1);
		}
		else if (is_redirection_operator(parsing->tokens[i]->proc_text))
			i++;
		i++;
	}
	return (arg_idx);
}

int	setup_exec_cmd(t_exec *exec, char **args, int arg_count)
{
	if (arg_count > 0)
	{
		exec->cmd = ft_strdup(args[0]);
		if (!exec->cmd)
		{
			free_double_array(args);
			return (-1);
		}
		exec->args = args;
		if (is_builtin_command(exec->cmd))
			exec->token = BUILTIN;
		else
			exec->token = ARG;
	}
	else
	{
		free(args);
		exec->cmd = NULL;
		exec->args = NULL;
	}
	return (0);
}
