/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:28 by pzurawic          #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	handle_empty_input(char *input, char *trimmed_input, t_data *data)
{
	if (!trimmed_input || *trimmed_input == '\0')
	{
		free(input);
		free(trimmed_input);
		data->parsing->input = NULL;
		return (true);
	}
	return (false);
}

static bool	handle_comment_input(char *input, char *trimmed_input, t_data *data)
{
	if (trimmed_input[0] == '#')
	{
		free(input);
		free(trimmed_input);
		data->parsing->input = NULL;
		return (true);
	}
	return (false);
}

bool	input_reader(t_data *data)
{
	char	*input;
	char	*trimmed_input;

	interactive_mode_signals(data);
	input = readline("minishell> ");
	if (!input)
	{
		printf("exit\n");
		free(input);
		return (false);
	}
	trimmed_input = ft_strtrim(input, " \t\n\r\f\v");
	if (handle_empty_input(input, trimmed_input, data))
		return (true);
	if (handle_comment_input(input, trimmed_input, data))
		return (true);
	add_history(input);
	data->parsing->input = input;
	free(trimmed_input);
	return (true);
}
