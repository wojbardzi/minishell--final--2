/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:55:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:46 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*token_type(t_tokens type)
{
	if (type == ARG)
		return ("ARG");
	else if (type == BUILTIN)
		return ("BUILTIN");
	else if (type == OPERATOR)
		return ("OPERATOR");
	else if (type == QUOT)
		return ("QUOT");
	return ("UNKNOWN");
}

void	print_tokens(t_token **tokens)
{
	int	i;

	printf("\nTokens:\n");
	i = 0;
	while (tokens[i])
	{
		printf("Token %d: ", i);
		if (tokens[i]->text)
			printf("Text taken: '%s', ", tokens[i]->text);
		if (tokens[i]->proc_text)
			printf("Processed text: '%s', ", tokens[i]->proc_text);
		printf("Type: %s\n", token_type(tokens[i]->type));
		i++;
	}
	printf("***************************\n\n");
}
