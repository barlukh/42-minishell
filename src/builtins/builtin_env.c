/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:37:15 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/22 09:32:39 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_env(t_exec *current, t_data *data)
{
	t_env	*current_env;

	if (ft_strcmp(current->cmd_arg[0], "env") == 0)
	{
		if (current->cmd_arg[1])
		{
			ft_putendl_fd(ERR_MSG_ENV, STDERR_FILENO);
			data->exit_status = 1;
			return (true);
		}
		current_env = data->lst_env;
		while (current_env)
		{
			if (current_env->assigned == true)
			{
				ft_putstr_fd(current_env->key, STDOUT_FILENO);
				write(STDOUT_FILENO, "=", 1);
				ft_putendl_fd(current_env->value, STDOUT_FILENO);
			}
			current_env = current_env->next;
		}
		data->exit_status = 0;
		return (true);
	}
	return (false);
}
