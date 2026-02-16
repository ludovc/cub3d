/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:47:26 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/16 16:47:26 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	set_position(float *x, float *y, float dx, float dy)
{
	*x += dx;
	*y += dy;
}

static void	movement(t_game *game)
{
	float	x;
	float	y;
	float	len;

	x = 0.0f;
	y = 0.0f;
	if (game->keys.w_pressed)
		set_position(&x, &y, game->player.dirx, game->player.diry);
	if (game->keys.s_pressed)
		set_position(&x, &y, -game->player.dirx, -game->player.diry);
	if (game->keys.a_pressed)
		set_position(&x, &y, -game->player.planex, -game->player.planey);
	if (game->keys.d_pressed)
		set_position(&x, &y, game->player.planex, game->player.planey);
	if (x != 0.0f || y != 0.0f)
	{
		len = sqrtf(x * x + y * y);
		if (len > 0.0f)
		{
			x /= len;
			y /= len;
		}
		move_player(game, x, y);
	}
}

void	set_player_dir(t_game *g)
{
	float	k;
	float	fov;

	fov = 60.0 * M_PI / 180.0;
	g->player.dirx = cosf(g->player.angle);
	g->player.diry = sinf(g->player.angle);
	k = tanf((float)fov / 2.0f);
	g->player.planex = -g->player.diry * k;
	g->player.planey = g->player.dirx * k;
}

static void	rotation(t_game *game)
{
	if (game->keys.left_pressed)
		game->player.angle -= CAMERA_ROTATION;
	if (game->keys.right_pressed)
		game->player.angle += CAMERA_ROTATION;
	if (game->keys.left_pressed || game->keys.right_pressed)
		set_player_dir(game);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->state == MENU)
	{
		show_menu(game);
		return (0);
	}
	movement(game);
	rotation(game);
	render_game(game);
	return (0);
}
