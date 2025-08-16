/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:13:09 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/16 17:32:15 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_check(int *return_value, t_exec *current, t_data *data)
{
	if (!current || !current->cmd_arg || !current->cmd_arg[0])
		return (BUILT_NO);
	*return_value = builtin_echo(current);
	if (*return_value != BUILT_NO)
		return (*return_value);
	*return_value = builtin_cd(current);
	if (*return_value != BUILT_NO)
		return (*return_value);
	*return_value = builtin_pwd(current, data);
	if (*return_value != BUILT_NO)
		return (*return_value);
	// return_value = builtin_export(current);
	// if (return_value != BUILT_NO)
	// 	return (return_value);
	// return_value = builtin_unset(current);
	// if (return_value != BUILT_NO)
	// 	return (return_value);
	*return_value = builtin_env(current, data);
	if (*return_value != BUILT_NO)
		return (*return_value);
	// return_value = builtin_exit(current);
	// if (return_value != BUILT_NO)
	// 	return (return_value);
	return (BUILT_NO);
}
