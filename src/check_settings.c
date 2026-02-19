/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <lucasu@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:46:24 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/19 16:45:24 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_file(char *str)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	else
	{
		close(fd);
		return (1);
	}
}

int	count_char(char *str, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	is_full_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_rgb(char *str)
{
	char	**parts;
	int		res;

	if (count_char(str, ',') != 2)
		return (0);
	res = 1;
	parts = ft_split(str, ',');
	if (strarr_len(parts) != 3)
	{
		res = 0;
	}
	else
	{
		if (!is_full_digit_string(parts[0]) || !is_full_digit_string(parts[1])
			|| !is_full_digit_string(parts[2]))
			res = 0;
		else if (ft_atoi(parts[0]) > 255)
			res = 0;
		else if (ft_atoi(parts[1]) > 255)
			res = 0;
		else if (ft_atoi(parts[2]) > 255)
			res = 0;
	}
	free_strarr(parts);
	return (res);
}

int	check_settings(t_settings *settings)
{
	if (!is_file(settings->no) || check_extension(settings->no, ".xpm"))
		return (0);
	if (!is_file(settings->so) || check_extension(settings->so, ".xpm"))
		return (0);
	if (!is_file(settings->we) || check_extension(settings->we, ".xpm"))
		return (0);
	if (!is_file(settings->ea) || check_extension(settings->ea, ".xpm"))
		return (0);
	if (!is_rgb(settings->f))
		return (0);
	if (!is_rgb(settings->c))
		return (0);
	return (1);
}
