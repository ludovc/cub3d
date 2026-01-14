#include "../inc/cub3d.h"

static void	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp,
			&game->img.line_length,
			&game->img.endian);
}

void	initialization(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	init_image(game);
	game->state = MENU;
	game->keys.w_pressed = 0;
	game->keys.a_pressed = 0;
	game->keys.s_pressed = 0;
	game->keys.d_pressed = 0;
	game->keys.left_pressed = 0;
	game->keys.right_pressed = 0;
}

static void	load_menu_image(t_game *game)
{
	int		w;
	int		h;

	game->menu_img.img = mlx_xpm_file_to_image(game->mlx,
			"xpm/menu.xpm", &w, &h);
	game->menu_img.addr = mlx_get_data_addr(game->menu_img.img,
			&game->menu_img.bpp, &game->menu_img.line_length,
			&game->menu_img.endian);
}

static int	load_wall_texture(t_game *game, t_img *img, char *path)
{
	int		w;
	int		h;

	img->img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	return (img->addr != NULL);
}

static int	load_all_wall_textures(t_game *game)
{
	if (!load_wall_texture(game, &game->txtrs.n_wall, NORTH_WALL))
		return (0);
	if (!load_wall_texture(game, &game->txtrs.s_wall, SOUTH_WALL))
		return (0);
	if (!load_wall_texture(game, &game->txtrs.e_wall, EAST_WALL))
		return (0);
	if (!load_wall_texture(game, &game->txtrs.w_wall, WEST_WALL))
		return (0);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_all_wall_textures(game))
		return (0);
	load_menu_image(game);
	return (1);
}

void	init_ray(t_game *g, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->ray_dirx = g->player.dirx + g->player.planex * camera_x;
	ray->ray_diry = g->player.diry + g->player.planey * camera_x;
	ray->mapx = (int)g->player.x;
	ray->mapy = (int)g->player.y;
	if (ray->ray_dirx == 0)
		ray->delta_distx = 1e30;
	else
		ray->delta_distx = fabs(1.0 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_disty = 1e30;
	else
		ray->delta_disty = fabs(1.0 / ray->ray_diry);
}
