/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:27:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/04 09:25:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	output(t_token **current);

int	builtin_echo(t_token **current)
{
	if (ft_strcmp((*current)->content, "echo") == 0)
	{
		if (((*current)->next)
			&& ft_strcmp((*current)->next->content, "-n") == 0)
		{
			while (((*current)->next)
				&& ft_strcmp((*current)->next->content, "-n") == 0)
				(*current) = (*current)->next;
			output(current);
		}
		else if (((*current)->next) && (*current)->next->type == TOK_ARG)
		{
			output(current);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
			ft_putendl_fd("", 1);
		get_data()->exit_status = 0;
		return (BUILT_YES);
	}
	return (BUILT_NO);
}

// Echoes the content of a token.
static void	output(t_token **current)
{
	while (((*current)->next) && (*current)->next->type == TOK_ARG)
	{
		(*current) = (*current)->next;
		ft_putstr_fd((*current)->content, 1);
		if (((*current)->next) && (*current)->next->type == TOK_ARG)
			write(STDOUT_FILENO, " ", 1);
	}
}
