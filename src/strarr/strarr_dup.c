/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:13:37 by lucasu            #+#    #+#             */
/*   Updated: 2025/11/05 17:32:15 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strarr.h"

int	strarr_len(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

char	**strarr_dup(char **arr)
{
	int		i;
	int		size;
	char	**res;

	size = strarr_len(arr);
	res = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
