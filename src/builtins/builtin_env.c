/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:37:15 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/16 17:33:31 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_exec *current, t_data *data)
{
	size_t	i;
	t_env	*current_env;

	i = 0;
	if (ft_strcmp(current->cmd_arg[i], "env") == 0)
	{
		if (current->cmd_arg[1])
		{
			ft_putendl_fd(ERR_MSG_ENV, STDERR_FILENO);
			data->exit_status = 1;
			return (BUILT_ERR);
		}
		current_env = data->lst_env;
		while (current_env)
		{
			ft_putstr_fd(current_env->key, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putendl_fd(current_env->value, STDOUT_FILENO);
			current_env = current_env->next;
		}
		get_data()->exit_status = 0;
		return (BUILT_YES);
	}
	return (BUILT_NO);
}
