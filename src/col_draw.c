/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:46:34 by lucasu            #+#    #+#             */
/*   Updated: 2026/02/16 16:46:34 by lucasu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_tex_y(t_game *game, t_column *col, t_ray *ray, int x)
{
	double	step;
	int		pixel;
	int		y;

	step = 1.0 * TEXTURE_HEIGHT / (double)ray->line_h;
	col->tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_h / 2.0) * step;
	y = ray->draw_start;
	while (y < ray->draw_end + 1)
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

void	draw_wall_texture(t_game *game, t_column *col, t_ray *ray, int x)
{
	col->tex_x = (int)(col->wall_x * (double)TEXTURE_WIDTH);
	if (col->tex_x < 0)
		col->tex_x = 0;
	if (col->tex_x >= TEXTURE_WIDTH)
		col->tex_x = TEXTURE_WIDTH - 1;
	if (!col->wall_tex || !col->wall_tex->addr)
		return ;
	draw_tex_y(game, col, ray, x);
}

void	draw_column(t_game *g, t_ray *ray, int x, t_column *col)
{
	int		y;
	int		ceil_color;
	int		floor_color;

	y = 0;
	ceil_color = rgb_string_to_int(g->settings->c);
	while (y < ray->draw_start)
		ft_mlx_pixel_put(&g->img, x, y++, ceil_color);
	draw_wall_texture(g, col, ray, x);
	y = ray->draw_end + 1;
	floor_color = rgb_string_to_int(g->settings->f);
	while (y < HEIGHT)
		ft_mlx_pixel_put(&g->img, x, y++, floor_color);
}

void	show_menu(t_game *game)
{
	if (game->menu_img.img)
		mlx_put_image_to_window(game->mlx, game->win, game->menu_img.img, 0, 0);
}
