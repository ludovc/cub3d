#include "../inc/cub3d.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	move_player(t_game *game, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = game->player.x + dx * MOVE_SPEED;
	new_y = game->player.y + dy * MOVE_SPEED;
	if (is_walkable(game->map, (int)new_x, (int)new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

int	is_walkable(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (!map[y] || !map[y][x])
		return (0);
	return (map[y][x] == '0' || is_spawn(map[y][x]));
}

void	draw_player(t_img *img, t_player *player)
{
	int		i;
	int		j;
	int		screen_x;
	int		screen_y;

	screen_x = MINIMAP_OFFSET_X + (int)(player->x * MINIMAP_TILE_SIZE) - 1;
	screen_y = MINIMAP_OFFSET_Y + (int)(player->y * MINIMAP_TILE_SIZE) - 1;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			ft_mlx_pixel_put(img, screen_x + i, screen_y + j, player->color);
			j++;
		}
		i++;
	}
}

void	update_player(t_game *game, int dx, int dy)
{
	float	old_x;
	float	old_y;

	old_x = game->player.x;
	old_y = game->player.y;
	move_player(game, dx, dy);
	if (old_x != game->player.x || old_y != game->player.y)
		render_game(game);
}
