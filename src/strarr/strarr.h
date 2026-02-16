/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:51:51 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/16 16:51:52 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRARR_H
# define STRARR_H

# include <stdlib.h>
# include "../../inc/libft.h"

void	free_strarr(char **strarr);
void	print_strarr(char **arr);
void	strarr_append(char ***arr, char *new_str);
char	**strarr_dup(char **arr);
void	strarr_remove(char **arr, char *str);
int		strarr_len(char **arr);
void	strarr_remove_index(char **arr, int index);
void	strarr_remove_var(char **arr, char *str);

#endif
