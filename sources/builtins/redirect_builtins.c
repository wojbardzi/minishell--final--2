/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wojti <wojti@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:48:32 by zuraw             #+#    #+#             */
/*   Updated: 2025/08/12 19:35:53 by wojti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin(t_data *data, t_exec *exec)
{
	if (!exec->cmd)
		return ;
	if (ft_strncmp(exec->cmd, "echo", 4) == 0)
		g_exit_code = builtin_echo(exec);
	else if (ft_strncmp(exec->cmd, "cd", 2) == 0)
		g_exit_code = builtin_cd(exec, data);
	else if (ft_strncmp(exec->cmd, "pwd", 3) == 0)
		g_exit_code = builtin_pwd();
	else if (ft_strncmp(exec->cmd, "export", 6) == 0)
		g_exit_code = builtin_export(exec, data);
	else if (ft_strncmp(exec->cmd, "unset", 5) == 0)
		g_exit_code = builtin_unset(exec, data);
	else if (ft_strncmp(exec->cmd, "env", 3) == 0)
		g_exit_code = builtin_env(exec->args, data->envp);
	else if (ft_strncmp(exec->cmd, "exit", 4) == 0)
		builtin_exit(exec, data);
}
