/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:43:56 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/30 15:24:09 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_sigint(int signum);

void	signals_heredoc(void)
{
	struct sigaction	action;

	g_signal = 0;
	ft_bzero(&action, sizeof(action));
	action.sa_handler = signal_handler_sigint;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
}

// Executes when SIGINT is received in heredoc.
static void	signal_handler_sigint(int signum)
{
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}
