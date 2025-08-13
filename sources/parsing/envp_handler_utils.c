/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:26:45 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_quotes(t_token *token, int *i, char *quot_mark)
{
	if (*quot_mark == 0 && (token->text[*i] == '\'' || token->text[*i] == '"'))
	{
		*quot_mark = token->text[*i];
		if (*quot_mark == '\'')
		{
			*i += skip_squot(&token->text[*i]) + 1;
			*quot_mark = 0;
			if (token->text[*i] == '\0')
				return (1);
		}
	}
	return (0);
}

static int	count_env_var(t_token *token, int i)
{
	int	len;

	len = 0;
	while (ft_isalnum(token->text[i + 1 + len])
		|| token->text[i + 1 + len] == '_')
		len++;
	if (len > 0 || token->text[i + 1] == '?')
		return (1);
	else
		return (1);
}

int	env_var_count(t_token *token)
{
	int		count;
	int		i;
	char	quot_mark;

	quot_mark = 0;
	count = 0;
	i = -1;
	while (token->text[++i])
	{
		if (handle_quotes(token, &i, &quot_mark))
			break ;
		if (token->text[i] == '$')
			count += count_env_var(token, i);
	}
	return (count);
}

void	get_env_var(t_token *token, int *i, int *j, char *value)
{
	int		len;
	char	*var_name;

	len = 0;
	while (token->text[*i + len] && (ft_isalnum(token->text[*i + len])
			|| token->text[*i + len] == '_'))
		len++;
	if (len == 0)
	{
		token->env_var[(*j)++] = ft_strdup("$");
		return ;
	}
	var_name = ft_substr(token->text, *i, len);
	value = get_env_value(var_name, token->envp);
	if (value)
		token->env_var[(*j)++] = ft_strdup(value);
	else
		token->env_var[(*j)++] = ft_strdup("");
	free(var_name);
	*i += len;
}

void	alloc_env_var(t_token *token)
{
	int	i;

	token->env_var = (char **)malloc(sizeof(char *)
			* (token->env_var_count + 1));
	if (!token->env_var)
		error_exit();
	i = -1;
	while (++i < token->env_var_count)
		token->env_var[i] = NULL;
}
