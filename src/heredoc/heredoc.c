/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:17:04 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/06 15:55:20 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_available_id(char **temp_name, size_t *i, t_data *data);
static void	create_temp_file(char *temp_name, t_data *data);

void	create_heredoc_temps(t_data *data)
{
	char	*temp_name;
	size_t	i;
	t_token	*current;

	i = 0;
	current = data->lst_tok;
	while (current)
	{
		if (current->type == TOK_HERE_QTD || current->type == TOK_HERE_UNQTD)
		{
			find_available_id(&temp_name, &i, data);
			create_temp_file(temp_name, data);
			i++;
		}
		current = current->next;
	}
}

// Finds the next available id number for heredoc file.
static void	find_available_id(char **temp_name, size_t *i, t_data *data)
{
	char	*id;

	while (true)
	{
		id = ft_itoa(*i);
		if (!id)
			error_heredoc_mem(data);
		*temp_name = ft_strjoin(TEMP, id);
		free(id);
		id = NULL;
		if (!*temp_name)
			error_heredoc_mem(data);
		if (access(*temp_name, F_OK) == 0)
		{
			free(*temp_name);
			(*i)++;
		}
		else
			break ;
	}
}

// Creates a new heredoc file.
static void	create_temp_file(char *temp_name, t_data *data)
{
	int		fd;

	fd = open(temp_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(temp_name);
	temp_name = NULL;
	if (fd == -1)
		error_heredoc_file(data);
	close(fd);
}
