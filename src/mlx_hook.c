#include "../inc/cub3d.h"

int handle_keypress(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (keycode == ESC_KEY)
		close_window(game);
	else if (keycode == W_KEY)
		game->keys.w_pressed = 1;
	else if (keycode == S_KEY)
		game->keys.s_pressed = 1;
	else if (keycode == A_KEY)
		game->keys.a_pressed = 1;
	else if (keycode == D_KEY)
		game->keys.d_pressed = 1;
    return (0);
}

int handle_keyrelease(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	
	if (keycode == W_KEY)
		game->keys.w_pressed = 0;
	else if (keycode == S_KEY)
		game->keys.s_pressed = 0;
	else if (keycode == A_KEY)
		game->keys.a_pressed = 0;
	else if (keycode == D_KEY)
		game->keys.d_pressed = 0;
    return (0);
}

static int is_wall(t_game *g, int mx, int my)
{
    if (my < 0 || mx < 0)
        return 1;
    if (!g->map || !g->map[my])
        return 1;
    // attenzione: righe normalizzate -> stessa lunghezza
    if (mx >= (int)ft_strlen(g->map[my]))
        return 1;

    // considera anche ' ' come non attraversabile se la tua normalizzazione usa spazi
    return (g->map[my][mx] == '1' || g->map[my][mx] == ' ');
}

static int shade(int color)
{
    // scurisci (per i lati y, side==1)
    int r = ((color >> 16) & 0xFF) / 2;
    int g = ((color >>  8) & 0xFF) / 2;
    int b = ((color      ) & 0xFF) / 2;
    return (r << 16) | (g << 8) | b;
}

void raycast_scene(t_game *g)
{
    for (int x = 0; x < WIDTH; x++)
    {
        double camera_x = 2.0 * x / (double)WIDTH - 1.0;
        double ray_dirx = g->player.dirx + g->player.planex * camera_x;
        double ray_diry = g->player.diry + g->player.planey * camera_x;

        int mapx = (int)g->player.x;
        int mapy = (int)g->player.y;

        double delta_distx = (ray_dirx == 0) ? 1e30 : fabs(1.0 / ray_dirx);
        double delta_disty = (ray_diry == 0) ? 1e30 : fabs(1.0 / ray_diry);

        int step_x, step_y;
        double side_distx, side_disty;

        if (ray_dirx < 0)
        {
            step_x = -1;
            side_distx = (g->player.x - mapx) * delta_distx;
        }
        else
        {
            step_x = 1;
            side_distx = (mapx + 1.0 - g->player.x) * delta_distx;
        }

        if (ray_diry < 0)
        {
            step_y = -1;
            side_disty = (g->player.y - mapy) * delta_disty;
        }
        else
        {
            step_y = 1;
            side_disty = (mapy + 1.0 - g->player.y) * delta_disty;
        }

        int hit = 0;
        int side = 0;
        while (!hit)
        {
            if (side_distx < side_disty)
            {
                side_distx += delta_distx;
                mapx += step_x;
                side = 0;
            }
            else
            {
                side_disty += delta_disty;
                mapy += step_y;
                side = 1;
            }
            if (is_wall(g, mapx, mapy))
                hit = 1;
        }

        double perp_dist;
        if (side == 0)
            perp_dist = (mapx - g->player.x + (1 - step_x) / 2.0) / ray_dirx;
        else
            perp_dist = (mapy - g->player.y + (1 - step_y) / 2.0) / ray_diry;

        if (perp_dist < 0.0001)
            perp_dist = 0.0001;

        int line_h = (int)(HEIGHT / perp_dist);
        int draw_start = -line_h / 2 + HEIGHT / 2;
        int draw_end   =  line_h / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        // colori base (poi li colleghi a settings->c e settings->f)
        int ceil_color = 0x202020;
        int floor_color = 0x404040;
        int wall_color = 0xAAAAAA;
        if (side == 1)
            wall_color = shade(wall_color);

        // disegna colonna
        for (int y = 0; y < draw_start; y++)
            ft_mlx_pixel_put(&g->img, x, y, ceil_color);

        for (int y = draw_start; y <= draw_end; y++)
            ft_mlx_pixel_put(&g->img, x, y, wall_color);

        for (int y = draw_end + 1; y < HEIGHT; y++)
            ft_mlx_pixel_put(&g->img, x, y, floor_color);
    }
}

void	render_game(t_game *game)
{
	clear_image(&game->img, BLACK);
	raycast_scene(game);
	render_frame(game);
}

int game_loop(void *param)
{
	t_game *game = (t_game *)param;
	
	// Controlla tutti i tasti premuti e muovi di conseguenza
	if (game->keys.w_pressed)
	{
		update_player(game, 0, -1);
	}
	if (game->keys.s_pressed)
	{
		update_player(game, 0, 1);
	}
	if (game->keys.a_pressed)
	{
		update_player(game, -1, 0);
	}
	if (game->keys.d_pressed)
	{
		update_player(game, 1, 0);
	}
	
	render_game(game);
		
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_all(game);
	exit(0);
	return (0);
}
