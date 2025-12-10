/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_remove2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:22:18 by lucasu            #+#    #+#             */
/*   Updated: 2025/10/06 15:22:27 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strarr.h"

int	strarr_find_var(char **arr, char *var)
{
	int		i;
	char	**str_parts;

	i = 0;
	while (arr[i])
	{
		str_parts = ft_split(arr[i], ' ');
		if (str_parts[0] && ft_strcmp(str_parts[0], var) == 0)
		{
			free_strarr(str_parts);
			return (i);
		}
		free_strarr(str_parts);
		i++;
	}
	return (-1);
}

void	strarr_remove_var(char **arr, char *var)
{
	int		index;

	index = strarr_find_var(arr, var);
	if (index >= 0)
	{
		strarr_remove_index(arr, index);
	}
}
