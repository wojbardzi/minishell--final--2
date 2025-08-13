/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:30:52 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 19:35:51 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Zwraca typ separatora
	0 - brak separatora
	1 - spacja
	2 - jeden znak
	3 - dwa znaki
*/
int	is_separator(t_parse *parsing, int i)
{
	if (parsing->input[i] == ' ')
		return (1);
	else if (look_for_operator(parsing->input[i]) == true)
	{
		if (parsing->input[i + 1] == parsing->input[i])
			return (3);
		return (2);
	}
	return (0);
}

static t_parse	*alloc_parsing(void)
{
	t_parse	*parsing;

	parsing = (t_parse *)malloc(sizeof(t_parse));
	if (!parsing)
		error_exit();
	parsing->input = NULL;
	parsing->words = NULL;
	parsing->tokens = NULL;
	parsing->operators = NULL;
	return (parsing);
}

t_exec	*alloc_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		error_exit();
	exec->operator = NULL;
	exec->cmd = NULL;
	exec->args = NULL;
	exec->token = 0;
	exec->out = STDOUT_FILENO;
	exec->in = STDIN_FILENO;
	exec->redirections = NULL;
	exec->next = NULL;
	exec->prev = NULL;
	exec->envp = NULL;
	return (exec);
}

void	copy_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		error_exit();
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
}

void	set_data(t_data *data, char **envp)
{
	copy_envp(data, envp);
	data->parsing = alloc_parsing();
	data->pids = NULL;
}
