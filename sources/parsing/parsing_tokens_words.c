/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_words.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:41:42 by zuraw             #+#    #+#             */
/*   Updated: 2024/11/20 17:27:22 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Jeżeli napotka znak cudzysłowia, to przeskakuje do końca cudzysłowia
*/
static void	process_quote(const char *input, int *i)
{
	char	quote;

	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[(*i)++];
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
	}
}

/*
	1. Sprawdza, czy dany znak jest separatorem
	2. Na podstawie typu separatora, dzieli input na tokeny
*/
static void	process_separator(t_parse *parsing, int *i, int *j, int *start)
{
	int	separator_type;

	if (parsing->input[*i] == '\0')
		return ;
	separator_type = is_separator(parsing, *i);
	if (separator_type == 0)
		return ;
	if (*i > *start)
		parsing->words[(*j)++] = ft_substr(parsing->input, *start, *i - *start);
	if (separator_type == 2)
	{
		parsing->words[(*j)++] = ft_substr(parsing->input, *i, 1);
		*start = *i + 1;
	}
	else if (separator_type == 3)
	{
		parsing->words[(*j)++] = ft_substr(parsing->input, *i, 2);
		*start = *i + 2;
		(*i)++;
	}
	else if (separator_type == 1)
		*start = *i + 1;
}

/*
	1. Alokuje pamięć dla tablicy słów
	2. Dzieli input na tokeny
*/
void	set_words_tab(t_parse *parsing)
{
	int	i;
	int	j;
	int	start;

	parsing->words = (char **)malloc(sizeof(char *)
			* (parsing->input_items + 1));
	if (!parsing->words)
		error_exit();
	parsing->words[parsing->input_items] = NULL;
	i = -1;
	start = 0;
	j = 0;
	while (parsing->input[++i] && j < parsing->input_items)
	{
		while (parsing->input[i] == '"' || parsing->input[i] == '\'')
			process_quote(parsing->input, &i);
		if (parsing->input[i] == '\0')
			break ;
		process_separator(parsing, &i, &j, &start);
	}
	if (i > start && j < parsing->input_items)
		parsing->words[j++] = ft_substr(parsing->input, start, i - start);
}
