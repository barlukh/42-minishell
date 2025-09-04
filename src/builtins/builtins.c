/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:13:09 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/04 13:49:53 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtins_check(t_exec *current, t_data *data)
{
	if (!current || !current->cmd_arg || !current->cmd_arg[0])
		return (false);
	if (builtin_cd(current, data))
		return (true);
	if (builtin_echo(current, data))
		return (true);
	if (builtin_env(current, data))
		return (true);
	if (builtin_exit(current, data))
		return (true);
	if (builtin_export(current, data))
		return (true);
	if (builtin_pwd(current, data))
		return (true);
	if (builtin_unset(current, data))
		return (true);
	return (false);
}

bool	is_builtins(char **command)
{
	if (!command || !command[0])
		return (false);
	if (!ft_strcmp(command[0], "cd"))
		return (true);
	if (!ft_strcmp(command[0], "echo"))
		return (true);
	if (!ft_strcmp(command[0], "env"))
		return (true);
	if (!ft_strcmp(command[0], "exit"))
		return (true);
	if (!ft_strcmp(command[0], "export"))
		return (true);
	if (!ft_strcmp(command[0], "pwd"))
		return (true);
	if (!ft_strcmp(command[0], "unset"))
		return (true);
	return (false);
}
