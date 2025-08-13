/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:44:49 by zuraw             #+#    #+#             */
/*   Updated: 2025/06/30 15:29:38 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_operator(t_token *token)
{
	if (look_for_operator(token->text[0]) == true)
		return (token->type = OPERATOR, 1);
	return (0);
}

static int	is_builtin(t_token *token)
{
	char	*tmp;
	int		len;

	len = ft_strlen(token->text);
	tmp = token->text;
	if (ft_strncmp(tmp, "echo", len) == 0)
		return (token->type = BUILTIN, 1);
	else if (ft_strncmp(tmp, "cd", len) == 0)
		return (token->type = BUILTIN, 1);
	else if (ft_strncmp(tmp, "pwd", len) == 0)
		return (token->type = BUILTIN, 1);
	else if (ft_strncmp(tmp, "export", len) == 0)
		return (token->type = BUILTIN, 1);
	else if (ft_strncmp(tmp, "unset", len) == 0)
		return (token->type = BUILTIN, 1);
	else if (ft_strncmp(tmp, "env", len) == 0)
		return (token->type = BUILTIN, 1);
	else if (ft_strncmp(tmp, "exit", len) == 0)
		return (token->type = BUILTIN, 1);
	return (0);
}

static int	is_quot(t_token *token)
{
	char	*tmp;
	int		j;

	tmp = token->text;
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == '"' || tmp[j] == '\'')
			return (token->type = QUOT, 1);
		j++;
	}
	return (0);
}

/*
	1. Tworzy tokeny z inputa
	2. Przypisuje im odpowiednie wartości
		- QUOT, OPERATOR, BUILTIN, ARG
*/
void	tokenize(t_parse *parsing)
{
	int	i;

	i = 0;
	set_words_tab(parsing);
	if (!parsing->words)
		error_exit();
	while (i < parsing->input_items)
	{
		parsing->tokens[i]->id = i;
		parsing->tokens[i]->text = parsing->words[i];
		if (is_quot(parsing->tokens[i]) == 1)
			;
		else if (is_operator(parsing->tokens[i]) == 1)
			;
		else if (is_builtin(parsing->tokens[i]) == 1)
			;
		else
			parsing->tokens[i]->type = ARG;
		i++;
	}
}
