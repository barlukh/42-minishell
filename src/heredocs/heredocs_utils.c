/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:19:10 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/08 18:42:44 by bgazur           ###   ########.fr       */
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
	free(input);
}

void	rename_heredoc_token(size_t i, t_token *current, t_data *data)
{
	char	*id;
	char	*tok_name;

	id = ft_itoa(i);
	if (!id)
		error_heredoc_mem(data);
	tok_name = ft_strjoin(TEMP, id);
	free(id);
	id = NULL;
	if (!tok_name)
		error_heredoc_mem(data);
	current->type = TOK_HERE;
	free(current->content);
	current->content = tok_name;
}
