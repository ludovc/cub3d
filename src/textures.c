#include "../inc/cub3d.h"

int	load_textures(t_game *game)
{
	int		w;
	int		h;

	game->txtrs.n_wall.img = mlx_xpm_file_to_image(game->mlx, NORTH_WALL, &w, &h);
	game->txtrs.n_wall.addr = mlx_get_data_addr(game->txtrs.n_wall.img,
			&game->txtrs.n_wall.bpp, &game->txtrs.n_wall.line_length, &game->txtrs.n_wall.endian);
	game->txtrs.s_wall.img = mlx_xpm_file_to_image(game->mlx, SOUTH_WALL, &w, &h);
	game->txtrs.s_wall.addr = mlx_get_data_addr(game->txtrs.s_wall.img,
			&game->txtrs.s_wall.bpp, &game->txtrs.s_wall.line_length, &game->txtrs.s_wall.endian);
	game->txtrs.e_wall.img = mlx_xpm_file_to_image(game->mlx, EAST_WALL, &w, &h);
	game->txtrs.e_wall.addr = mlx_get_data_addr(game->txtrs.e_wall.img,
			&game->txtrs.e_wall.bpp, &game->txtrs.e_wall.line_length, &game->txtrs.e_wall.endian);
	game->txtrs.w_wall.img = mlx_xpm_file_to_image(game->mlx, WEST_WALL, &w, &h);
	game->txtrs.w_wall.addr = mlx_get_data_addr(game->txtrs.w_wall.img,
			&game->txtrs.w_wall.bpp, &game->txtrs.w_wall.line_length, &game->txtrs.w_wall.endian);
	load_menu_image(game);
	if (!game->txtrs.n_wall.img || !game->txtrs.s_wall.img || !game->txtrs.e_wall.img || !game->txtrs.w_wall.img)
		return (0);
	return (1);
}

void	draw_wall_texture(t_game *game, t_column *col, t_ray *ray, int x)
{
	int		y;
	double	step;
	int		pixel;
	int		new_draw_end;
	
	new_draw_end = ray->draw_end + 1;
	col->tex_x = (int)(col->wall_x * (double)TEXTURE_WIDTH);
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= TEXTURE_WIDTH)
		col->tex_x = TEXTURE_WIDTH - 1;
	if (!col->wall_tex || !col->wall_tex->addr)
		return ;
	step = 1.0 * TEXTURE_HEIGHT / (double)ray->line_h;
	col->tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_h / 2.0) * step;
	y = ray->draw_start;
	while (y < new_draw_end)
	{
		col->tex_y = (int)col->tex_pos;
		col->tex_pos += step;
		if (col->tex_y < 0)
			col->tex_y = 0;
		if (col->tex_y >= TEXTURE_HEIGHT)
			col->tex_y = TEXTURE_HEIGHT - 1;
		pixel = *(int *)(col->wall_tex->addr
				+ col->tex_y * col->wall_tex->line_length
				+ col->tex_x * (col->wall_tex->bpp / 8));
		ft_mlx_pixel_put(&game->img, x, y, pixel);
		y++;
	}
}

// Utility: converte una stringa RGB (es: "220,100,0") in un int colore 0xRRGGBB usando solo funzioni della libft
int	rgb_string_to_int(const char *rgb_str)
{
	int		i;
	int		r;
	int		g;
	int		b;
	char	**split;

	r = 0;
	g = 0;
	b = 0;
	if (!rgb_str)
		return (0);
	split = ft_split(rgb_str, ',');
	if (split)
	{
		if (split[0])
			r = ft_atoi(split[0]);
		if (split[1])
			g = ft_atoi(split[1]);
		if (split[2])
			b = ft_atoi(split[2]);
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
	}
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	draw_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		color;

	color = rgb_string_to_int(game->settings->c);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game)
{
	int		x;
	int		y;
	int		color;

	color = rgb_string_to_int(game->settings->f);
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}
