/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_skip_var(char *env_var, char **args)
{
	int	k;
	int	len;

	k = 0;
	while (args[k])
	{
		len = ft_strlen(args[k]);
		if (ft_strncmp(args[k], env_var, len) == 0 && env_var[len] == '=')
			return (1);
		k++;
	}
	return (0);
}

char	**build_new_envp(char **envp, char **new_envp, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!should_skip_var(envp[i], args))
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
				return (NULL);
			j++;
		}
		i++;
	}
	return (new_envp);
}
