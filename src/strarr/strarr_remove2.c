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

#include "minishell.h"

int	strarr_find_unset(char **arr, char *str)
{
	int		i;
	char	**str_parts;

	i = 0;
	while (arr[i])
	{
		str_parts = ft_split(arr[i], '=');
		if (ft_strcmp(str_parts[0], str) == 0)
		{
			free_strarr(str_parts);
			return (i);
		}
		free_strarr(str_parts);
		i++;
	}
	return (-1);
}

void	strarr_remove_for_unset(char **arr, char *str)
{
	int		index;

	index = strarr_find_unset(arr, str);
	if (index >= 0)
	{
		strarr_remove_index(arr, index);
	}
}
