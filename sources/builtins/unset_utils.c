/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:20:00 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_duplicate(char **args, int index)
{
	int	i;

	if (!args || index < 0)
		return (0);
	i = 0;
	while (i < index)
	{
		if (ft_strncmp(args[i], args[index], ft_strlen(args[index])) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	find_var_in_envp(char **envp, char *arg)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(arg);
	while (envp[j])
	{
		if (ft_strncmp(arg, envp[j], len) == 0 && envp[j][len] == '=')
			return (1);
		j++;
	}
	return (0);
}

int	count_args_in_envp(char **envp, char **args)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (!is_duplicate(args, i) && find_var_in_envp(envp, args[i]))
			count++;
		i++;
	}
	return (count);
}

char	**allocate_new_envp(char **envp, int vars_to_remove)
{
	char	**new_envp;
	int		i;
	int		new_size;

	i = 0;
	while (envp[i])
		i++;
	new_size = i - vars_to_remove + 1;
	new_envp = (char **)malloc(sizeof(char *) * new_size);
	if (!new_envp)
		return (NULL);
	new_envp[new_size - 1] = NULL;
	return (new_envp);
}
