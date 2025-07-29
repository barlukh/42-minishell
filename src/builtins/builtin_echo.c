/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:27:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 14:38:03 by bgazur           ###   ########.fr       */
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
		else if (((*current)->next) && (*current)->next->type == TOK_WORD)
		{
			output(current);
			write(1, "\n", 1);
		}
		else
			ft_putendl_fd("", 1);
		return (BUILT_YES);
	}
	return (BUILT_NO);
}

// Echoes the content of a token.
static void	output(t_token **current)
{
	while (((*current)->next) && (*current)->next->type == TOK_WORD)
	{
		(*current) = (*current)->next;
		ft_putstr_fd((*current)->content, 1);
		if (((*current)->next) && (*current)->next->type == TOK_WORD)
			write(1, " ", 1);
	}
}
