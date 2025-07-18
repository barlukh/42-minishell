/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array_specified.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:48:00 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/18 13:29:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_array_index(char **arr, size_t i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr[i]);
	free(arr);
}
