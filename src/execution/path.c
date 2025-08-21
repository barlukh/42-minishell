
#include "minishell.h"

int	node_count(t_env *temp, int count)
{
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	**rebuild_env(t_env lst_env, int i, int count)
{
	t_env	*temp;
	char	**env_array;
	char	*key_eq;

	temp = &lst_env;
	key_eq = NULL;
	count = node_count(temp, i);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return NULL;
	temp = &lst_env;
	while (temp)
	{
		key_eq = ft_strjoin(temp->key, "=");
		if (!key_eq)
			return NULL;
		if (temp->value != NULL)
			env_array[i] = ft_strjoin(key_eq, temp->value);
		free(key_eq);
		if (!env_array[i])
			return NULL;
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

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
	char	*full;
	char	*tmp;
	int i = 0;

	if (!command || !command[0])
		return NULL;
	// if the cmd has already the fullpath
	if (access(command[0], X_OK) == 0)
		return (ft_strdup(command[0]));
	path_env = get_env_value(env);
	if (!path_env)
		return NULL;
	paths = ft_split(path_env, ':');
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_array(paths), NULL);
		full = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (!full)
			return (ft_free_array(paths), NULL);
		if (access(full, X_OK) == 0)
			return (ft_free_array(paths), full);
		free(full);
		i++;
	}
	ft_free_array(paths);
	return NULL;
}
