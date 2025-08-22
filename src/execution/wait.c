
#include "minishell.h"

bool	wait_process(pid_t *pid, t_data *data)
{
	int		i;
	int		status;
	int		cmds_count;
	pid_t	term_pid;

	i = 0;
	cmds_count = data->cmd_count;
	while (i < cmds_count)
	{
		term_pid = waitpid(data->pids[i], &status, 0);
		if (term_pid == -1)
			return (false);
		if (term_pid == pid[cmds_count - 1] && (WIFEXITED(status)))
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
	return (true);
}
