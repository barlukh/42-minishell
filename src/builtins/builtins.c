/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:13:09 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/25 09:44:53 by bgazur           ###   ########.fr       */
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
