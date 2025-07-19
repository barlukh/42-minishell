/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/19 13:58:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_tok(char *input_line, t_token **lst, char *content)
{
	free(input_line);
	input_line = NULL;
	ft_lstclear(lst);
	lst = NULL;
	free(content);
	content = NULL;
	ft_putendl_fd("Error allocating memory", 2);
	exit(1);
}
