/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:15:20 by lucasu            #+#    #+#             */
/*   Updated: 2025/10/06 15:22:36 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strarr.h"

void	strarr_shift(char **arr, int start, int size)
{
	int		i;

	i = start;
	while (i < size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = NULL;
}

void	strarr_remove_index(char **arr, int index)
{
	int		size;

	size = strarr_len(arr);
	free(arr[index]);
	strarr_shift(arr, index, size);
}

int	strarr_find(char **arr, char *str)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	strarr_remove(char **arr, char *str)
{
	int		index;

	index = strarr_find(arr, str);
	if (index >= 0)
	{
		strarr_remove_index(arr, index);
	}
}
