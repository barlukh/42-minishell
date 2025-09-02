
#include "minishell.h"

void	clean_and_exit(t_data *data, char **env, int exit_code)
{
	ft_lst_env_clear(&get_data()->lst_env);
	get_data()->lst_env = NULL;
	ft_lst_exec_clear(&data->lst_exec);
	data->lst_exec = NULL;
	ft_free_array(env);
	clear_history();
	data->exit_status = exit_code;
	exit(data->exit_status);
}

void	parent_fds(t_exec *node)
{
	if (node->fd[WRITE] > 2)
		safe_close(&node->fd[WRITE]);
	if (get_data()->tmp_fd > 2)
		safe_close(&get_data()->tmp_fd);
	if (node->fd[READ] > 2)
		get_data()->tmp_fd = node->fd[READ];
}
