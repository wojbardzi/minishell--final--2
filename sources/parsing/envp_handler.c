/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:01:02 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	size_t	len;

	len = strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/*
	Przesuwa wskaźnik na koniec pojedynczego cudzysłowu
	$VAR w pojedynczym cudzysłowie nie jest brany pod uwagę
*/
static void	handle_quotes(t_token *token, char *quot_mark, int *i)
{
	*quot_mark = token->text[*i];
	if (*quot_mark == '\'')
	{
		*i += skip_squot(&token->text[*i]) + 1;
		*quot_mark = 0;
	}
}

static void	handle_var(t_token *token, int *i, int *j, char *value)
{
	if (token->text[*i] == '?')
	{
		value = ft_itoa(g_exit_code);
		token->env_var[(*j)++] = value;
		(*i)++;
	}
	else
		get_env_var(token, i, j, value);
}

void	envp_handler(t_token *token)
{
	int		i;
	int		j;
	char	*value;
	char	quot_mark;

	token->env_var_count = env_var_count(token);
	alloc_env_var(token);
	i = 0;
	j = 0;
	quot_mark = 0;
	value = NULL;
	while (token->text[i])
	{
		if (quot_mark == 0 && (token->text[i] == '\'' || token->text[i] == '"'))
			handle_quotes(token, &quot_mark, &i);
		else if (token->text[i] == '$')
		{
			i++;
			handle_var(token, &i, &j, value);
		}
		else
			i++;
	}
}
