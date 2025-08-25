/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:50:49 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/25 09:35:01 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_option(char *content);
static void	unset_action(char *content, t_data *data);

bool	builtin_unset(t_exec *current, t_data *data)
{
	size_t	i;

	i = 1;
	if (ft_strcmp(current->cmd_arg[0], "unset") == 0)
	{
		if (current->cmd_arg[1] && is_invalid_option(current->cmd_arg[1]))
		{
			ft_putendl_fd(ERR_MSG_UNSET, STDERR_FILENO);
			data->exit_status = 2;
			return (true);
		}
		while (current->cmd_arg[i])
		{
			unset_action(current->cmd_arg[i], data);
			i++;
		}
		data->exit_status = 0;
		return (true);
	}
	return (false);
}

// Checks if the argument is an invalid option.
static bool	is_invalid_option(char *content)
{
	if (!content || content[0] != '-')
		return (false);
	if (content[1] == '\0')
		return (false);
	if (content[1] != '-')
		return (true);
	if (content[1] == '-' && content[2] == '\0')
		return (false);
	return (true);
}

// Finds and unsets a variable from env.
static void unset_action(char *content, t_data *data)
{
	t_env	*current;
	t_env	*next;

	current = data->lst_env;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(content, current->key) == 0)
			ft_lst_env_remove(&data->lst_env, current);
		current = next;
	}
}
