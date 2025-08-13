/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:40:17 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/10 19:04:05 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exec_envp(t_exec *exec, char **envp)
{
	t_exec	*tmp_exec;

	tmp_exec = exec;
	if (!exec || !envp)
		return ;
	while (exec)
	{
		exec->envp = envp;
		exec = exec->next;
	}
	exec = tmp_exec;
}

static int	update_existing_envp(char **envp, char *arg)
{
	int		i;
	int		len;

	i = 0;
	while (envp[i])
	{
		len = 0;
		while (arg[len] && arg[len] != '=')
			len++;
		if (ft_strncmp(envp[i], arg, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			if (envp[i] == NULL)
				error_exit();
			return (1);
		}
		i++;
	}
	return (0);
}

char	**create_new_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		error_exit();
	new_envp[i + 1] = NULL;
	return (new_envp);
}

char	*prepare_envp_entry(char *arg)
{
	int		len;
	char	*result;
	char	*tmp;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (arg[len] == '\0')
	{
		tmp = ft_strjoin(arg, "=");
		if (!tmp)
			error_exit();
		result = ft_strdup(tmp);
		free(tmp);
	}
	else
		result = ft_strdup(arg);
	if (!result)
		error_exit();
	return (result);
}

void	update_envp(t_data *data, t_exec *exec, int *j)
{
	if (!data || !exec || !exec->args || !j || !exec->args[*j])
		return ;
	if (update_existing_envp(data->envp, exec->args[*j]))
	{
		(*j)++;
		return ;
	}
	create_and_update_envp(data, exec->args[*j]);
	(*j)++;
}
