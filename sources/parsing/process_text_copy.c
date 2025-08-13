/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_text_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:34:33 by zuraw             #+#    #+#             */
/*   Updated: 2024/11/28 13:34:01 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_variable(t_token *token, int *i, int *j)
{
	int	y;

	y = 0;
	if (!token->env_var || !token->env_var[token->curr_ev])
		return ;
	(*i)++;
	if (token->text[*i] == '?')
	{
		token->proc_text[(*j)++] = token->env_var[token->curr_ev][y++];
		token->curr_ev++;
		(*i)++;
		return ;
	}
	while (token->env_var[token->curr_ev][y])
		token->proc_text[(*j)++] = token->env_var[token->curr_ev][y++];
	token->curr_ev++;
	while (ft_isalnum(token->text[*i]) || token->text[*i] == '_')
		(*i)++;
}

void	manage_sq(t_token *token, int *i, int *j, char *quot_mark)
{
	(*i)++;
	while (token->text[*i] && token->text[*i] != '\'')
		token->proc_text[(*j)++] = token->text[(*i)++];
	(*i)++;
	(*quot_mark) = 0;
}

void	manage_dq(t_token *token, int *i, int *j, char *quot_mark)
{
	(*i)++;
	while (token->text[*i] && token->text[*i] != '"')
	{
		if (token->text[*i] == '$')
			expand_variable(token, i, j);
		else
		{
			token->proc_text[(*j)++] = token->text[*i];
			(*i)++;
		}
	}
	if (token->text[*i] == '"')
		(*i)++;
	(*quot_mark) = 0;
}

/*
	1. Alokuje pamięć na tekst gotowy do przekazania
	2. Śledzi cudzysłowy
	3. Przepisuje tekst do proc_text obsługując cudzysołowy
		i zmienne środowiskowe
*/
void	copy_text(t_token *token, int len, char quot_mark)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc_proc_text(token, len);
	quot_mark = 0;
	while (token->text[i])
	{
		track_quot_mark(token, &quot_mark, i);
		if (token->text[i] == '\'' && quot_mark == '\'')
			manage_sq(token, &i, &j, &quot_mark);
		else if (token->text[i] == '"' && quot_mark == '"')
			manage_dq(token, &i, &j, &quot_mark);
		else if (token->text[i] == '$')
			expand_variable(token, &i, &j);
		else if (token->text[i] != '\0')
			token->proc_text[j++] = token->text[i++];
	}
	token->proc_text[j] = '\0';
}
