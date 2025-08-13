/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:31 by pzurawic          #+#    #+#             */
/*   Updated: 2025/08/12 19:35:54 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

static void	process_input(t_data *data)
{
	int	exit_status;

	data->exec = alloc_exec();
	parsing(data);
	exit_status = execute_pipeline(data);
	if (exit_status != -1)
		g_exit_code = exit_status;
}

static void	cleanup_exec(t_data *data)
{
	if (data->exec)
	{
		while (data->exec && data->exec->prev)
			data->exec = data->exec->prev;
		clear_exec(data->exec);
		data->exec = NULL;
	}
}

static void	main_loop(t_data *data)
{
	while (input_reader(data) == true)
	{
		if (data->parsing->input == NULL)
			continue ;
		process_input(data);
		cleanup_exec(data);
		clear_parsing(data->parsing);
	}
}

/*
** Do odpalenia bez leaków readline:
** valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
** --suppressions=readline.supp ./minishell
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	g_exit_code = 0;
	set_data(&data, envp);
	main_loop(&data);
	exit_clear(&data);
	return (g_exit_code);
}
