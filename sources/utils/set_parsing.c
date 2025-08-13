/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:29:21 by zuraw             #+#    #+#             */
/*   Updated: 2025/06/30 15:29:17 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	hq(t_parse *parsing, int *i, char *in_quote, int *in_word)
{
	if (!*in_quote && (parsing->input[*i] == '"' || parsing->input[*i] == '\''))
	{
		*in_quote = parsing->input[*i];
		if (!*in_word)
		{
			parsing->input_items++;
			*in_word = 1;
		}
	}
	else if (*in_quote && parsing->input[*i] == *in_quote)
		*in_quote = 0;
}

static void	handle_separators(t_parse *parsing, int *i, int *in_word)
{
	int	separator_type;

	separator_type = is_separator(parsing, *i);
	if (separator_type == 2 || separator_type == 3)
	{
		parsing->input_items++;
		if (separator_type == 3)
			(*i)++;
		*in_word = 0;
	}
	else if (separator_type == 0 && !*in_word)
	{
		parsing->input_items++;
		*in_word = 1;
	}
	else if (separator_type == 1)
		*in_word = 0;
}

static int	count_input_items(t_parse *parsing)
{
	int		i;
	int		in_word;
	char	in_quote;

	parsing->input_items = 0;
	i = 0;
	in_word = 0;
	in_quote = 0;
	while (parsing->input[i])
	{
		hq(parsing, &i, &in_quote, &in_word);
		if (!in_quote)
			handle_separators(parsing, &i, &in_word);
		i++;
	}
	if (in_quote != 0)
	{
		printf("%s", QUOT_ERROR);
		error_exit();
	}
	return (parsing->input_items);
}

static void	alloc_tokens(t_parse *parsing, t_exec *exec)
{
	t_token	**tokens;
	int		i;

	tokens = (t_token **)malloc(sizeof(t_token *) * (parsing->input_items + 1));
	if (!tokens)
		error_exit();
	tokens[parsing->input_items] = NULL;
	parsing->tokens = tokens;
	i = -1;
	while (++i < parsing->input_items)
	{
		parsing->tokens[i] = (t_token *)malloc(sizeof(t_token));
		if (!parsing->tokens[i])
			error_exit();
		parsing->tokens[i]->text = NULL;
		parsing->tokens[i]->env_var = NULL;
		if (exec && exec->envp && exec->envp[0] == NULL)
			exec->envp = parsing->data->envp;
		else
			parsing->tokens[i]->envp = parsing->data->envp;
		parsing->tokens[i]->proc_text = NULL;
		parsing->tokens[i]->type = 0;
		parsing->tokens[i]->curr_ev = 0;
		parsing->tokens[i]->env_var_count = 0;
	}
}

/*
	- Alokuje miejsce dla operatorów oraz je ustawia
	- Zlicza ile będzie tokenów - count_input_items
	- Alokuje miejsce dla tokenów
*/
void	set_parsing(t_parse *parsing, t_data *data)
{
	parsing->data = data;
	parsing->operators = (char *)malloc(sizeof(char) * 4);
	if (!parsing->operators)
		error_exit();
	set_operators(parsing->operators);
	parsing->input_items = count_input_items(parsing);
	alloc_tokens(parsing, data->exec);
}
