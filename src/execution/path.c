
#include "minishell.h"

char	*get_env_value(char **envp)
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

char	*path_finder(char **command, char **env)
{
	char	*path_env;
	char	**paths;
	char	*final_path;
	int i = 0;

	if (!command || !command[0])
		return (NULL);
	if (ft_strchr(command[0], '/'))
		return (command[0]);
	if (access(command[0], F_OK | X_OK) == 0)
		return (command[0]);
	path_env = get_env_value(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	while (paths && paths[i])
	{
		final_path = path_joiner(paths, command, i);
		i++;
	}
	if (!final_path)	
		ft_free_array(paths);
	return (final_path);
}

char	*path_joiner(char **paths, char **command, int i)
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

void	path_checker(t_data *data, t_exec *node,  char **env, char *path)
{
	struct	stat sb;

	if (ft_strcmp(node->cmd_arg[0], ".") == 0)
	{
		ft_putendl_fd(".: filename argument required", STDERR_FILENO);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		clean_and_exit(data, node, env, 127);
	}
	if ((node->cmd_arg[0] && node->cmd_arg[0][0] != '\0') && 
			stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putendl_fd2(node->cmd_arg[0], ": Is a directory", STDERR_FILENO);
		clean_and_exit(data, node, env, 126);
	}
}
