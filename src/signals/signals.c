/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:28:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/04 18:19:02 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_sigint(int signum);

void	signals(void)
{
	struct sigaction	action;
	struct sigaction	ignore;

	ft_bzero(&action, sizeof(action));
	ft_bzero(&ignore, sizeof(ignore));
	action.sa_handler = signal_handler_sigint;
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&action.sa_mask);
	sigemptyset(&ignore.sa_mask);
	action.sa_flags = SA_RESTART;
	ignore.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &ignore, NULL);
}

// Executes when a signal is received.
static void	signal_handler_sigint(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}
