#include "../inc/cub3d.h"

static void	clear_image(t_img *img, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	raycast_scene(t_game *g)
{
	int			x;
	t_column	col;

	x = 0;
	while (x < WIDTH)
	{
		t_ray ray;

		init_ray(g, x, &ray);
		set_ray_steps(&ray, g->player.x, g->player.y);
		digital_differential_analysis(g, &ray);
		calc_perp_dist(&ray, g->player.x, g->player.y);
		get_line_limits(&ray);
		calculate_wall_x(g, &ray, &col);
		texture_selection(g, &ray, &col);
		draw_column(g, &ray, x, &col);
		x++;
	}
}

void	render_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void render_game(t_game *game)
{
	if (!game || !game->img.img || !game->map)
		return ;
	clear_image(&game->img, BLACK);
	raycast_scene(game);
	draw_minimap(game);
	draw_player(&game->img, &game->player);
	render_frame(game);
}