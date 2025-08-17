/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:39:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/17 13:45:09 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_invalid_option(char *content);

int	builtin_pwd(t_exec *current, t_data *data)
{
	char	*cwd;
	size_t	i;

	i = 0;
	if (ft_strcmp(current->cmd_arg[i], "pwd") == 0)
	{
		if (current->cmd_arg[1] && is_invalid_option(current->cmd_arg[1]))
		{
			ft_putendl_fd(ERR_MSG_PWD, STDERR_FILENO);
			data->exit_status = 2;
			return (BUILT_ERR);
		}
		cwd = NULL;
		cwd = getcwd(cwd, 0);
		if (!cwd)
			error_general_mem(data);
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		get_data()->exit_status = 0;
		return (BUILT_YES);
	}
	return (BUILT_NO);
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
