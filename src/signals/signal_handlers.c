/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:24:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/07 13:28:17 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_main(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}

void	signal_handler_heredoc(int signum)
{
	g_signal = 128 + signum;
	get_data()->exit_status = g_signal;
}
