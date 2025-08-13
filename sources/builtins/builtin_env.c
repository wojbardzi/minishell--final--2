/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:36:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/12 21:14:37 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_env_args(char **args)
{
	if (args && args[0] && args[1])
	{
		if (ft_strncmp(args[1], "", 1) != 0 && access(args[1], F_OK) == -1)
		{
			printf("env: %s: No such file or directory\n", args[1]);
			return (127);
		}
	}
	return (0);
}

static void	print_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	builtin_env(char **args, char **envp)
{
	int	validation_result;

	if (!envp)
		return (1);
	validation_result = validate_env_args(args);
	if (validation_result != 0)
		return (validation_result);
	print_env_vars(envp);
	return (0);
}
