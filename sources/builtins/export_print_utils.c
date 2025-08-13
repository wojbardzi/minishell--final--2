/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:00:00 by wojti             #+#    #+#             */
/*   Updated: 2025/08/03 13:48:47 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**allocate_sorted_array(char **envp)
{
	char	**sorted_envp;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	sorted_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!sorted_envp)
		error_exit();
	sorted_envp[i] = NULL;
	return (sorted_envp);
}

static void	copy_and_sort_envp(char **envp, char **sorted_envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		sorted_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	bubble_sort(sorted_envp, i);
}

static void	print_and_free_sorted(char **sorted_envp)
{
	int	i;

	i = -1;
	while (sorted_envp[++i])
	{
		printf("declare -x %s\n", sorted_envp[i]);
		free(sorted_envp[i]);
	}
	free(sorted_envp);
}

void	print_sorted_array(char **envp)
{
	char	**sorted_envp;

	sorted_envp = allocate_sorted_array(envp);
	if (!sorted_envp)
		return ;
	copy_and_sort_envp(envp, sorted_envp);
	print_and_free_sorted(sorted_envp);
}
