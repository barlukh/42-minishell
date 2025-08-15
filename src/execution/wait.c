
#include "minishell.h"

// This function waits all the children and return the statu of the last child.
bool	wait_processes(pid_t *pid, t_data *data)
{
	int		i;
	int		status;
	int		cmds_count;
	pid_t	term_pid;

	i = 0;
	cmds_count = 0;
	while(tmp != NULL)
	{
		if (data->lst_tok->type == TOK_CMD)
			cmds_count++;
		tmp = data->lst_tok->next;
	}
	while (i > cmds_count)
	{
		term_pid = waitpid(-1, &status, 0);
		if (term_pid == -1)
			return (false);
		if (term_pid == pid[0] || term_pid == pid[1])
		{
			i++;
			if (term_pid == pid[1] && (WIFEXITED(status)))
				data->exit_status = WEXITSTATUS(status);
		}
	}
	return (true);
}
