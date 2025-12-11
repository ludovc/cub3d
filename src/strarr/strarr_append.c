/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:10:26 by lucasu            #+#    #+#             */
/*   Updated: 2025/11/05 17:39:38 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strarr.h"

char	**strarr_expand(char **arr)
{
	int		size_old;
	int		size_new;
	int		i;
	char	**res;

	size_old = strarr_len(arr);
	size_new = size_old + 1;
	res = malloc(sizeof(char *) * (size_new + 1));
	i = 0;
	while (i < size_old)
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = NULL;
	res[i + 1] = NULL;
	free(arr);
	return (res);
}

void	strarr_append(char ***arr, char *new_str)
{
	int		size;

	size = strarr_len(*arr);
	*arr = strarr_expand(*arr);
	(*arr)[size] = ft_strdup(new_str);
}
