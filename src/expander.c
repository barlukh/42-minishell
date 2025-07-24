/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:57:25 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/23 18:21:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expander(t_env **lst_env, t_token **lst_tok)
{
	t_env	*current_env;
	t_token	*current_tok;

	current_env = *lst_env;
	current_tok = *lst_tok;
	while (current_tok)
	{
		while (*(current_tok->content))
		{
			if (*(current_tok->content) == '$' && quote != '\'')
			{
				content++;
				while (current)
				{
					if (strcmp(content, current->key) == 0)
						printf("%s\n", current->value);
					current = current->next;
				}
			}
			content++;
		}


		current_tok = current_tok->next;
	}


}
