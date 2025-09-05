/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:38:11 by edlucca           #+#    #+#             */
/*   Updated: 2025/09/05 19:14:09 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char **envp);
static char	*path_joiner(char **paths, char **command, int i);

char	*path_finder(char **command, char **env)
{
	char	*path_env;
	char	**paths;
	char	*final_path;
	int		i;

	i = 0;
	if (!command || !command[0] || !command[0][0])
		return (NULL);
	if (ft_strchr(command[0], '/') != NULL || access(command[0], X_OK) == 0)
		return (command[0]);
	path_env = get_env_value(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	while (paths && paths[i])
	{
		final_path = path_joiner(paths, command, i);
		if (final_path)
			break ;
		i++;
	}
	if (!final_path)
		ft_free_array(paths);
	return (final_path);
}

// Retrieve the variable path form the env
static char	*get_env_value(char **envp)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	command = "PATH";
	path = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(command, envp[i], ft_strlen(command)) == 0
			&& envp[i][ft_strlen(command)] == '=')
		{
			path = ft_strchr(envp[i], '=') + 1;
			break ;
		}
	}
	if (!path)
		return (NULL);
	return (path);
}

// Join the command with the path.
static char	*path_joiner(char **paths, char **command, int i)
{
	char	*full;
	char	*tmp;

	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
		return (ft_free_array(paths), NULL);
	full = ft_strjoin(tmp, command[0]);
	free(tmp);
	if (!full)
		return (ft_free_array(paths), NULL);
	if (access(full, F_OK) == 0)
		return (ft_free_array(paths), full);
	free(full);
	return (NULL);
}
