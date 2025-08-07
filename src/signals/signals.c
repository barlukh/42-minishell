/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:28:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/07 13:32:23 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_sigaction_sigint(void);
static void	set_sigaction_sigquit(void);

void	signals_main(void)
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
	action.sa_handler = signal_handler_main;
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

void	signals_heredoc(void)
{
	struct sigaction	action;

	g_signal = 0;
	ft_bzero(&action, sizeof(action));
	action.sa_handler = signal_handler_heredoc;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
}
