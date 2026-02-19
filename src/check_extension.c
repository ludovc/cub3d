/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:07:45 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/19 16:54:13 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_extension(const char *str, const char *ext)
{
	int		ls;
	int		le;

	printf("Controllo estensione di '%s' contro '%s'\n", str, ext);
	if (!str || !ext)
		return (1);
	ls = ft_strlen(str);
	le = ft_strlen(ext);
	if (le > ls)
	{
		ft_printf("Errore: estensione sbagliata\n");
		return (1);
	}
	if (ft_strcmp(str + (ls - le), ext) != 0)
	{
		ft_printf("Errore: estensione sbagliata\n");
		return (1);
	}
	return (0);
}
