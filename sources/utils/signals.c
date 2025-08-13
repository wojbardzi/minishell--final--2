/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:33 by pzurawic          #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigaction_error(int signal)
{
	if (signal == SIGINT)
		perror("sigaction SIGINT");
	else if (signal == SIGQUIT)
		perror("sigaction SIGQUIT");
	else if (signal == SIGPIPE)
		perror("sigaction SIGPIPE");
	exit(EXIT_FAILURE);
}

void	interactive_mode_signals(t_data *data)
{
	setup_sigint(data);
	setup_sigquit(data);
	setup_sigpipe(data);
}
