/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:28:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/30 15:17:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_sigaction_sigint(void);
static void	set_sigaction_sigquit(void);
static void	signal_handler_sigint(int signum);

void	signals_readline(void)
{
	g_signal = 0;
	rl_done = 0;
	rl_event_hook = NULL;
	set_sigaction_sigint();
	set_sigaction_sigquit();
}

// Sets the sigaction for SIGINT.
static void	set_sigaction_sigint(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = signal_handler_sigint;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
}

// Sets the sigaction for SIGQUIT.
static void	set_sigaction_sigquit(void)
{
	struct sigaction	ignore;

	ft_bzero(&ignore, sizeof(ignore));
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
}

// Executes when SIGINT is received in the readline prompt.
static void	signal_handler_sigint(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}
