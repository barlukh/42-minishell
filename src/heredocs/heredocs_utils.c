/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:19:10 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/08 10:22:44 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_event_hook(void)
{
	if (g_signal == 130)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	heredoc_write(char *input, int *fd)
{
	write(*fd, input, ft_strlen(input));
	write(*fd, "\n", 1);
}
