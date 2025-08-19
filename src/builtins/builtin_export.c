/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:18:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/19 09:49:51 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_option(char *content);

bool	builtin_export(t_exec *current, t_data *data)
{
	size_t	i;

	i = 0;
	if (ft_strcmp(current->cmd_arg[i], "export") == 0)
	{
		i++;
		if (current->cmd_arg[i] && is_invalid_option(current->cmd_arg[i]))
		{
			ft_putendl_fd(ERR_MSG_PWD, STDERR_FILENO);
			data->exit_status = 2;
			return (true);
		}
		while (current->cmd_arg[i])
		{
			export(current->cmd_arg[i], data);
			i++;
		}
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

// Main function to export a variable.
static bool	export(char *content, t_data *data)
{
	
}
