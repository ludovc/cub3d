#include "cub3d.h"

void move_player(t_player *player, int dx, int dy)
{
	player->x += dx * 4;
	player->y += dy * 4;
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
