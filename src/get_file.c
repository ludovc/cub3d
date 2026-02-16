/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:47:32 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/16 16:47:33 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	texture_selection(t_game *g, t_ray *ray, t_column *col)
{
	if (ray->side == 0)
	{
		if (ray->ray_dirx > 0)
			col->wall_tex = &g->txtrs.e_wall;
		else
			col->wall_tex = &g->txtrs.w_wall;
	}
	else
	{
		if (ray->ray_diry > 0)
			col->wall_tex = &g->txtrs.s_wall;
		else
			col->wall_tex = &g->txtrs.n_wall;
	}
}

// file preso dal mio so_long, e riadattato leggermente

char	*ft_strjoin_fs1(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

int	get_r(char *path)
{
	int		fd;
	char	*row;
	int		res;

	fd = open(path, O_RDONLY);
	res = 0;
	row = ft_get_next_line(fd);
	free(row);
	res++;
	while (row)
	{
		row = ft_get_next_line(fd);
		free(row);
		res++;
	}
	close(fd);
	return (res);
}

void	remove_newline(char *str)
{
	char	*newline_point;

	if (!str)
		return ;
	newline_point = ft_strchr(str, '\n');
	if (newline_point)
		*newline_point = '\0';
}

char	**get_file(char *path)
{
	char	**file;
	char	*row;
	int		number_row;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	number_row = get_r(path);
	file = (char **) malloc((number_row + 1) * sizeof(char *));
	if (!file)
		return (NULL);
	i = 0;
	while (i < number_row)
	{
		row = ft_get_next_line(fd);
		remove_newline(row);
		file[i] = row;
		i++;
	}
	file[i] = NULL;
	close(fd);
	return (file);
}
