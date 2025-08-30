/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:44:36 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/30 15:23:47 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_sigaction_sigint(void);
static void	set_sigaction_sigquit(void);

void	signals_exec_child(void)
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
	action.sa_handler = SIG_DFL;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
}

// Sets the sigaction for SIGQUIT.
static void	set_sigaction_sigquit(void)
{
	struct sigaction	ignore;

	ft_bzero(&ignore, sizeof(ignore));
	ignore.sa_handler = SIG_DFL;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGQUIT, &ignore, NULL);
}
