#include "../inc/cub3d.h"

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
