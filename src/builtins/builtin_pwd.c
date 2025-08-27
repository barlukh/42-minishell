/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:39:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/26 15:03:44 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_option(char *content);

bool	builtin_pwd(t_exec *current, t_data *data)
{
	char	*pwd;

	if (ft_strcmp(current->cmd_arg[0], "pwd") == 0)
	{
		if (current->cmd_arg[1] && is_invalid_option(current->cmd_arg[1]))
		{
			ft_putendl_fd(ERR_MSG_PWD, STDERR_FILENO);
			data->exit_status = 2;
			return (true);
		}
		pwd = pwd_get(data);
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
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
