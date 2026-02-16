/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:50:26 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/16 16:50:27 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player_spawn(char **map, float *x, float *y)
{
	int		row;
	int		col;

	if (!map || !x || !y)
		return (0);
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (is_spawn(map[row][col]))
			{
				*x = (float)col + 0.5f;
				*y = (float)row + 0.5f;
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}

void	set_angle_from_spawn(t_game *g, char spawn)
{
	if (spawn == 'N')
		g->player.angle = -M_PI_2;
	if (spawn == 'S')
		g->player.angle = M_PI_2;
	if (spawn == 'E')
		g->player.angle = 0.0f;
	if (spawn == 'W')
		g->player.angle = M_PI;
	set_player_dir(g);
}

void	spawn_player(t_game *game)
{
	if (!find_player_spawn(game->map, &game->player.x, &game->player.y))
	{
		printf("An error occurred while spawning\n");
		free_all(game);
		exit(1);
	}
	set_angle_from_spawn(game,
		game->map[(int)game->player.y][(int)game->player.x]);
	game->player.color = RED;
}
