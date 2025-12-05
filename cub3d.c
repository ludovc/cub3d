/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 cub3d.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lucasu <lucasu@student.42firenze.it>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/11 16:00:39 by lucasu			   #+#	  #+#			  */
/*	 Updated: 2025/11/11 16:03:20 by lucasu			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include <stdlib.h>

#define ESC_KEY 65307
#define UP_KEY 65362
#define DOWN_KEY 65364
#define LEFT_KEY 65361
#define RIGHT_KEY 65363

typedef struct s_player {
	int x;
	int y;
	int color;
} t_player;

int	close_window()
{
	exit(0);
	return (0);
}

typedef struct s_game {
	void *mlx;
	void *win;
	t_player player;
} t_game;

void move_player(t_player *player, int dx, int dy)
{
	player->x += dx * 5;
	player->y += dy * 5;
}

void draw_player(void *mlx_ptr, void *win_ptr, t_player *player)
{
    int i;
	int j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, player->x + i, player->y + j, player->color);
			j++;
		}
		i++;
	}
}

void clear_player(void *mlx_ptr, void *win_ptr, t_player *player)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, player->x + i, player->y + j, 0x000000);
			j++;
		}
		i++;
	}
}

void update_player(t_game *game, int dx, int dy)
{
	clear_player(game->mlx, game->win, &game->player);
	move_player(&game->player, dx, dy);
	draw_player(game->mlx, game->win, &game->player);
}


int handle_key(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == UP_KEY)
		update_player(game, 0, -1);
	else if (keycode == DOWN_KEY)
		update_player(game, 0, 1);
	else if (keycode == LEFT_KEY)
		update_player(game, -1, 0);
	else if (keycode == RIGHT_KEY)
		update_player(game, 1, 0);
    return (0);
}

int	main()
{
	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 500, 500, "Cub3D - Move with arrows");
	game.player.x = 100;
	game.player.y = 100;
	game.player.color = 0x39FF14;
	
	draw_player(game.mlx, game.win, &game.player);

	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_hook(game.win, 2, 1, handle_key, &game);
	mlx_loop(game.mlx);
}
