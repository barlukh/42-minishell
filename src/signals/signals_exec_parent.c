/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:44:36 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/30 15:44:43 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_sigaction_sigint(void);
static void	set_sigaction_sigquit(void);
static void	signal_handler_sigint(int signum);
static void	signal_handler_sigquit(int signum);

void	signals_exec_parent(void)
{
	g_signal = 0;
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
	ignore.sa_handler = signal_handler_sigquit;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &ignore, NULL);
}

// Executes when SIGINT is received in the execution parent path.
static void	signal_handler_sigint(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}

// Executes when SIGQUIT is received in the execution parent path.
static void	signal_handler_sigquit(int signum)
{
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}
