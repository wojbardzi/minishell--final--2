/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:54:06 by zuraw             #+#    #+#             */
/*   Updated: 2025/07/27 17:31:22 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Założenie funkcji:
	1. Zalokowanie pamięci dla tokenów
	2. Tokenizacja
	3. Przetworzenie tekstu dla każdego tokenu
	4. Przeniesienie informacji o tokenach do struktury exec
*/
int	parsing(t_data *data)
{
	int	i;

	set_parsing(data->parsing, data);
	tokenize(data->parsing);
	i = -1;
	while (data->parsing->tokens[++i])
		process_text(data->parsing->tokens[i]);
	push_to_exec(data->parsing, data->exec);
	return (0);
}
