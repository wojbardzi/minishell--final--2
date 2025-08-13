/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:51:33 by zuraw             #+#    #+#             */
/*   Updated: 2025/06/30 15:29:53 by zuraw            ###   ########.fr       */
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
			*i += skip_squot(&token->text[*i]);
			*quot_mark = 0;
			return (1);
		}
	}
	else if (*quot_mark != 0 && token->text[*i] == *quot_mark)
	{
		*quot_mark = 0;
		return (1);
	}
	return (0);
}

static void	handle_var(const char *text, int *i, int *in_var, int *var_len)
{
	if (text[*i] == '$' && (ft_isalnum(text[*i + 1]) || text[*i + 1] == '_'))
	{
		*in_var = 1;
		(*i)++;
		(*var_len)++;
		while (ft_isalnum(text[*i]) || text[*i] == '_')
		{
			(*var_len)++;
			(*i)++;
		}
		*in_var = 0;
	}
	else if (text[*i] == '$')
	{
		(*var_len)++;
		(*i)++;
	}
}

static int	calc_var_len(t_token *token)
{
	int		i;
	int		in_var;
	int		var_len;
	char	quot_mark;

	i = -1;
	in_var = 0;
	var_len = 0;
	quot_mark = 0;
	while (token->text[++i])
	{
		if (handle_quotes(token, &i, &quot_mark))
			;
		else if (quot_mark != '\'' && token->text[i])
			handle_var(token->text, &i, &in_var, &var_len);
		if (token->text[i] == '\0')
			break ;
	}
	return (var_len);
}

static int	calc_env_vars(t_token *token)
{
	int	tot_len;
	int	i;

	tot_len = 0;
	i = 0;
	while (i < token->env_var_count)
	{
		tot_len += ft_strlen(token->env_var[i]);
		i++;
	}
	return (tot_len);
}

/*
	1. Oblicza długość nowego tekstu gotowego do execa
	2. Jeżelie nie jest ' to pobiera i oblicza długość $VAR's
	3. Uruchamia COPY_TEXT, która przepisuje $VAR do proc_text
*/
void	process_text(t_token *token)
{
	char	quot_mark;
	int		len;
	int		var_len;
	int		env_var_len;

	len = ft_strlen(token->text);
	quot_mark = 0;
	if (token->type == BUILTIN || token->type == OPERATOR)
		token->proc_text = ft_strdup(token->text);
	else
	{
		len = dec_by_quot_mark(token, len);
		var_len = calc_var_len(token);
		len -= var_len;
		envp_handler(token);
		if (token->env_var != NULL)
			env_var_len = calc_env_vars(token);
		else
			env_var_len = 0;
		len += env_var_len;
		copy_text(token, len, quot_mark);
	}
}
