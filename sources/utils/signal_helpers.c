/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	interactive_sigint(int signo)
{
	(void) signo;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	setup_signal_mask(sigset_t *mask, t_data *data)
{
	if (sigemptyset(mask) == -1)
	{
		clear_parsing(data->parsing);
		clear_exec(data->exec);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	setup_sigint(t_data *data)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = interactive_sigint;
	setup_signal_mask(&sa_int.sa_mask, data);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		sigaction_error(SIGINT);
}

void	setup_sigquit(t_data *data)
{
	struct sigaction	sa_quit;

	sa_quit.sa_handler = SIG_IGN;
	setup_signal_mask(&sa_quit.sa_mask, data);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		sigaction_error(SIGQUIT);
}

void	setup_sigpipe(t_data *data)
{
	struct sigaction	sa_pipe;

	sa_pipe.sa_handler = SIG_DFL;
	setup_signal_mask(&sa_pipe.sa_mask, data);
	sa_pipe.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa_pipe, NULL) == -1)
		sigaction_error(SIGPIPE);
}
