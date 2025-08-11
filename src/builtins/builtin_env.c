/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:37:15 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/11 13:12:00 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_token **current, t_data *data)
{
	t_env	*current_env;

	if (ft_strcmp((*current)->content, "env") == 0)
	{
		current_env = data->lst_env;
		while (current_env)
		{
			ft_putstr_fd(current_env->key, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putendl_fd(current_env->value, STDOUT_FILENO);
			current_env = current_env->next;
		}
		return (BUILT_YES);
	}
	return (BUILT_NO);
}
