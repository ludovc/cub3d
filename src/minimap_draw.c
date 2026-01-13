#include "../inc/cub3d.h"

void	draw_h_edge(t_img *img, int x0, int y0, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < MINIMAP_WALL_THICKNESS)
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

void	draw_v_edge(t_img *img, int x0, int y0, int color)
{
	int		x;
	int		y;

	x = 0;
	while (x < MINIMAP_WALL_THICKNESS)
	{
		y = 0;
		while (y < MINIMAP_TILE_SIZE)
		{
			ft_mlx_pixel_put(img, x0 + x, y0 + y, color);
			y++;
		}
		x++;
	}
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

void	draw_minimap(t_game *game)
{
	int		row_len;
	int		x;
	int		y;
	char	c;

	if (!game || !game->map)
		return ;
	y = 0;
	while (game->map[y])
	{
		row_len = (int)ft_strlen(game->map[y]);
		x = 0;
		while (x < row_len)
		{
			c = game->map[y][x];
			draw_cell(game, x, y, c);
			x++;
		}
		y++;
	}
}

void	draw_borders(t_game *g, int cx, int cy)
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	char	n;

	x0 = MINIMAP_OFFSET_X + (cx * MINIMAP_TILE_SIZE);
	y0 = MINIMAP_OFFSET_Y + (cy * MINIMAP_TILE_SIZE);
	x1 = x0 + MINIMAP_TILE_SIZE;
	y1 = y0 + MINIMAP_TILE_SIZE;
	n = bounds_check(g->map, cy - 1, cx);
	if (n == '0' || is_spawn(n))
		draw_h_edge(&g->img, x0, y0, GREEN);
	n = bounds_check(g->map, cy + 1, cx);
	if (n == '0' || is_spawn(n))
		draw_h_edge(&g->img, x0, y1 - MINIMAP_WALL_THICKNESS, GREEN);
	n = bounds_check(g->map, cy, cx - 1);
	if (n == '0' || is_spawn(n))
		draw_v_edge(&g->img, x0, y0, GREEN);
	n = bounds_check(g->map, cy, cx + 1);
	if (n == '0' || is_spawn(n))
		draw_v_edge(&g->img, x1 - MINIMAP_WALL_THICKNESS, y0, GREEN);
}
