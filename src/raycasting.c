#include "../inc/cub3d.h"
#include <stdio.h>

static int is_wall(t_game *g, int mx, int my)
{
    if (my < 0 || mx < 0)
        return(1);
    if (!g->map || !g->map[my])
        return(1);
    if (mx >= (int)ft_strlen(g->map[my]))
        return(1);
    return(g->map[my][mx] == '1' || g->map[my][mx] == ' '); // questo secondo controllo non dovrebbe servire
}


static void set_ray_steps(t_ray *ray, double player_x, double player_y)
{
    if (ray->ray_dirx < 0)
    {
        ray->step_x = -1;
        ray->side_distx = (player_x - ray->mapx) * ray->delta_distx;
    }
    else
    {
        ray->step_x = 1;
        ray->side_distx = (ray->mapx + 1.0 - player_x) * ray->delta_distx;
    }
    if (ray->ray_diry < 0)
    {
        ray->step_y = -1;
        ray->side_disty = (player_y - ray->mapy) * ray->delta_disty;
    }
    else
    {
        ray->step_y = 1;
        ray->side_disty = (ray->mapy + 1.0 - player_y) * ray->delta_disty;
    }
}

static void digital_differential_analysis(t_game *g, t_ray *ray)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (ray->side_distx < ray->side_disty)
        {
            ray->side_distx += ray->delta_distx;
            ray->mapx += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_disty += ray->delta_disty;
            ray->mapy += ray->step_y;
            ray->side = 1;
        }
        if (is_wall(g, ray->mapx, ray->mapy))
            hit = 1;
    }
}

static void calc_perp_dist(t_ray *ray, double player_x, double player_y)
{
    if (ray->side == 0) // vcerticale
        ray->perp_dist = (ray->mapx - player_x + (1 - ray->step_x) / 2.0) / ray->ray_dirx;

    else // orrizzontale
        ray->perp_dist = (ray->mapy - player_y + (1 - ray->step_y) / 2.0) / ray->ray_diry;

    if (ray->perp_dist < 0.5)
        ray->perp_dist = 0.5; // evita divisioni per zero
}

static void get_line_limits(t_ray *ray)
{
    ray->line_h = (int)(HEIGHT / ray->perp_dist); // l'altezza è inversamente proporzionale alla distanza perpendicaolare
    ray->draw_start = -(ray->line_h) / 2 + HEIGHT / 2;
    ray->draw_end = (ray->line_h) / 2 + HEIGHT / 2; // queste due centrano la colonna verticale disegnata su schermo
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1; // questi due if si assicurano che non si esca dai bordi
}

static void init_ray(t_game *g, int x, t_ray *ray)
{
    double camera_x;

    camera_x = 2.0 * x / (double)WIDTH - 1.0;
    ray->ray_dirx = g->player.dirx + g->player.planex * camera_x;
    ray->ray_diry = g->player.diry + g->player.planey * camera_x;
    ray->mapx = (int)g->player.x;
    ray->mapy = (int)g->player.y;
    if (ray->ray_dirx == 0)
        ray->delta_distx = 1e30; // evita errori di calcolo e divisioni per zero con un valore grandissimo
    else
        ray->delta_distx = fabs(1.0 / ray->ray_dirx);
    if (ray->ray_diry == 0)
        ray->delta_disty = 1e30;
    else
        ray->delta_disty = fabs(1.0 / ray->ray_diry);
}

void raycast_scene(t_game *g)
{
    int x = 0;

    while (x < WIDTH)
    {
        t_ray ray;

        init_ray(g, x, &ray);
        set_ray_steps(&ray, g->player.x, g->player.y);
        digital_differential_analysis(g, &ray);
        calc_perp_dist(&ray, g->player.x, g->player.y);
        get_line_limits(&ray); // qui dentro probabilmente clippi draw_start/draw_end

        // ---- 1) line_height "vero" (NON clampato) ----
        // se nel tuo ray hai già ray.line_height, usa quello invece di ricalcolare.
        int line_height_full = (int)(HEIGHT / ray.perp_dist);
        if (line_height_full < 1)
            line_height_full = 1;

        // ---- 2) calcolo wall_x corretto (già ok) ----
        double wall_x;
        if (ray.side == 0)
            wall_x = g->player.y + ray.perp_dist * ray.ray_diry;
        else
            wall_x = g->player.x + ray.perp_dist * ray.ray_dirx;
        wall_x -= floor(wall_x);

        // ---- 3) selezione texture ----
        t_img *wall_tex;
        if (ray.side == 0)
            wall_tex = (ray.ray_dirx > 0) ? &g->txtrs.e_wall : &g->txtrs.w_wall;
        else
            wall_tex = (ray.ray_diry > 0) ? &g->txtrs.s_wall : &g->txtrs.n_wall;

        // ---- 4) soffitto ----
        int y = 0;
        int ceil_color = rgb_string_to_int(g->settings->c);
        while (y < ray.draw_start)
            ft_mlx_pixel_put(&g->img, x, y++, ceil_color);

        // ---- 5) muro (NUOVA FIRMA: passa line_height_full) ----
        draw_wall_texture(g, wall_tex, x,
                          ray.draw_start, ray.draw_end + 1,
                          line_height_full, wall_x);

        // ---- 6) pavimento ----
        y = ray.draw_end + 1;
        int floor_color = rgb_string_to_int(g->settings->f);
        while (y < HEIGHT)
            ft_mlx_pixel_put(&g->img, x, y++, floor_color);

        x++;
    }
}

void render_game(t_game *game)
{
    clear_image(&game->img, BLACK);
    raycast_scene(game);
    draw_minimap(game);
    render_frame(game);
}

int game_loop(void *param)
{
    t_game *game = (t_game *)param;
    if (game->state == MENU)
    {
        show_menu(game);
        return (0);
    }
    float move_x = 0.0f;
    float move_y = 0.0f;
    if (game->keys.w_pressed)
    {
        move_x += game->player.dirx;
        move_y += game->player.diry;
    }
    if (game->keys.s_pressed)
    {
        move_x -= game->player.dirx;
        move_y -= game->player.diry;
    }
    if (game->keys.a_pressed)
    {
        move_x -= game->player.planex;
        move_y -= game->player.planey;
    }
    if (game->keys.d_pressed)
    {
        move_x += game->player.planex;
        move_y += game->player.planey;
    }
    if (move_x != 0.0f || move_y != 0.0f)
    {
        float len = sqrtf(move_x * move_x + move_y * move_y);
        if (len > 0.0f)
        {
            move_x /= len;
            move_y /= len;
        }
        move_player(game, move_x, move_y);
    }
    if (game->keys.left_pressed)
    {
        game->player.angle -= CAMERA_ROTATION;
        set_player_dir(game);
    }
    if (game->keys.right_pressed)
    {
        game->player.angle += CAMERA_ROTATION;
        set_player_dir(game);
    }
    render_game(game);
    return (0);
}


