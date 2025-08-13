/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_text_copy_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:44:40 by zuraw             #+#    #+#             */
/*   Updated: 2024/11/29 15:15:08 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	alloc_proc_text(t_token *token, int len)
{
	token->proc_text = malloc(sizeof(char) * (len + 1));
	if (!token->proc_text)
		error_exit();
	token->proc_text[len] = '\0';
}

void	track_quot_mark(t_token *token, char *quot_mark, int i)
{
	if ((token->text[i] == '\'' || token->text[i] == '"') && *quot_mark == 0)
		(*quot_mark) = token->text[i];
	else if ((token->text[i] == '\'' || token->text[i] == '"')
		&& *quot_mark != 0)
		(*quot_mark) = 0;
}
