/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:52:37 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/21 13:47:01 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_tok(char *input, t_token **lst, char *content)
{
	free(input);
	input = NULL;
	ft_lstclear(lst);
	lst = NULL;
	free(content);
	content = NULL;
	clear_history();
	ft_putendl_fd("Error allocating memory", 2);
	exit(EXIT_FAILURE);
}
