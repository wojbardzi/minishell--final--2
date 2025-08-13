/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_text_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:49:32 by zuraw             #+#    #+#             */
/*   Updated: 2024/11/22 12:51:01 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_squot(char *text)
{
	int	i;

	i = 1;
	while (text[i] && text[i] != '\'')
		i++;
	return (i);
}

int	dec_by_quot_mark(t_token *token, int len)
{
	int		i;
	char	current_quote;

	i = -1;
	current_quote = 0;
	while (token->text[++i])
	{
		if (current_quote == 0 && (token->text[i] == '\''
				|| token->text[i] == '"'))
		{
			current_quote = token->text[i];
			len--;
		}
		else if (current_quote != 0 && token->text[i] == current_quote)
		{
			len--;
			current_quote = 0;
		}
	}
	return (len);
}
