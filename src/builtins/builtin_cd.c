/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/29 13:54:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cd_home(t_data *data);
static bool	is_invalid_option(char *content);
static bool	is_dash(char *arg, size_t *i, t_data *data);
static bool	cd_action(char *arg, t_data *data);

bool	builtin_cd(t_exec *current, t_data *data)
{
	size_t	i;

	i = 1;
	if (ft_strcmp(current->cmd_arg[0], "cd") == 0)
	{
		if (!current->cmd_arg[1])
			return (cd_home(data));
		if (current->cmd_arg[1] && is_invalid_option(current->cmd_arg[1]))
		{
			ft_putendl_fd(ERR_MSG_CD, STDERR_FILENO);
			data->exit_status = 2;
			return (true);
		}
		if (current->cmd_arg[2])
		{
			ft_putendl_fd(ERR_MSG_CDARG, STDERR_FILENO);
			data->exit_status = 1;
			return (true);
		}
		if (is_dash(current->cmd_arg[1], &i, data) == true)
			return (true);
		cd_action(current->cmd_arg[i], data);
		return (true);
	}
	return (false);
}

// Runs cd into HOME directory.
static bool	cd_home(t_data *data)
{
	char	*cwd;
	char	*home;

	cwd = pwd_get(data);
	home = home_get(data);
	if (!home)
		ft_putendl_fd(ERR_MSG_CDHOME, STDERR_FILENO);
	else if (chdir(home) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		return (wd_set(cwd, data));
	free(cwd);
	data->exit_status = 1;
	return (true);
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

// Checks for the presence of a dash character and performs action accordingly.
static bool	is_dash(char *arg, size_t *i, t_data *data)
{
	char	*cwd;
	char	*oldpwd;

	if (ft_strcmp(arg, "-") == 0)
	{
		cwd = pwd_get(data);
		oldpwd = oldpwd_get(data);
		if (!oldpwd)
			ft_putendl_fd(ERR_MSG_CDSET, STDERR_FILENO);
		else if (chdir(oldpwd) == -1)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
		else
		{
			ft_putendl_fd(oldpwd, STDOUT_FILENO);
			return (wd_set(cwd, data));
		}
		free(cwd);
		return (data->exit_status = 1, true);
	}
	if (arg[0] == '-')
		(*i)++;
	return (false);
}

// Runs the cd builtin with the selected argument.
static bool	cd_action(char *arg, t_data *data)
{
	char	*cwd;

	cwd = pwd_get(data);
	if (chdir(arg) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		return (wd_set(cwd, data));
	free(cwd);
	data->exit_status = 1;
	return (true);
}
