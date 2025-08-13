/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:46:37 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exit(void)
{
	perror("Error");
	exit(1);
}

void	exit_clear(t_data *data)
{
	rl_clear_history();
	if (data->parsing)
	{
		clear_parsing(data->parsing);
		free(data->parsing);
		data->parsing = NULL;
	}
	if (data->exec)
	{
		while (data->exec->prev)
			data->exec = data->exec->prev;
		clear_exec(data->exec);
		data->exec = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	free_data_envp(data);
}

static void	free_env_var(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->env_var_count)
	{
		free(token->env_var[i]);
		i++;
	}
	free(token->env_var);
	token->env_var = NULL;
}

void	free_tokens(t_parse *parsing)
{
	int	i;

	i = 0;
	while (parsing->tokens[i])
	{
		free_env_var(parsing->tokens[i]);
		if (parsing->tokens[i]->proc_text)
			free(parsing->tokens[i]->proc_text);
		parsing->tokens[i]->envp = NULL;
		free(parsing->tokens[i]);
		i++;
	}
	free(parsing->tokens);
}

void	free_words(t_parse *parsing)
{
	int	i;

	i = 0;
	while (parsing->words[i])
	{
		free(parsing->words[i]);
		i++;
	}
	free(parsing->words);
}
