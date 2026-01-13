#include "../inc/cub3d.h"

static void	fill_tile(t_img *img, int x0, int y0, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < MINIMAP_TILE_SIZE)
	{
		x = 0;
		while (x < MINIMAP_TILE_SIZE)
		{
			ft_mlx_pixel_put(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

char	bounds_check(char **map, int y, int x)
{
	int		row_len;

	if (y < 0 || x < 0)
		return (' ');
	if (!map || !map[y])
		return (' ');
	row_len = (int)ft_strlen(map[y]);
	if (x >= row_len)
		return (' ');
	return (map[y][x]);
}

void	draw_cell(t_game *game, int x, int y, char c)
{
	if (c == '1' || c == ' ')
	{
		fill_tile(&game->img,
			MINIMAP_OFFSET_X + (x * MINIMAP_TILE_SIZE),
			MINIMAP_OFFSET_Y + (y * MINIMAP_TILE_SIZE),
			GREY);
		if (c == '1')
			draw_borders(game, x, y);
	}
}

static int	is_walkable(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (!map[y] || !map[y][x])
		return (0);
	return (map[y][x] == '0' || is_spawn(map[y][x]));
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
