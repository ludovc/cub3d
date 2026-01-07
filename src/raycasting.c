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
    return(g->map[my][mx] == '1' || g->map[my][mx] == ' ' || g->map[my][mx] == '2' || g->map[my][mx] == '3'); // accetta anche '2' e '3' come muro
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

    if (ray->perp_dist < 0.01)
        ray->perp_dist = 0.01; // evita divisioni per zero
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
        char tile = g->map[ray.mapy][ray.mapx];
        if (tile == '2')
            wall_tex = &g->txtrs.win_condition;
        else if (tile == '3')
            wall_tex = &g->txtrs.loose_condition;
        else if (ray.side == 0)
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

// Blending helper
static int blend_color_alpha(int base, int overlay, float alpha) {
    int r = ((1.0f - alpha) * ((base >> 16) & 0xFF) + alpha * ((overlay >> 16) & 0xFF));
    int g = ((1.0f - alpha) * ((base >> 8) & 0xFF) + alpha * ((overlay >> 8) & 0xFF));
    int b = ((1.0f - alpha) * (base & 0xFF) + alpha * (overlay & 0xFF));
    return (r << 16) | (g << 8) | b;
}

// Disegna una texture centrata con alpha blending
void draw_centered_alpha_texture(t_game *game, t_img *tex, float alpha) {
    if (!tex || !tex->img || !tex->addr) return;
    int win_w = WIDTH;
    int win_h = HEIGHT;
    int tex_w = tex->width;
    int tex_h = tex->height;
    int x0 = (win_w - tex_w) / 2;
    int y0 = (win_h - tex_h) / 2;
    for (int y = 0; y < tex_h; y++) {
        for (int x = 0; x < tex_w; x++) {
            int win_x = x0 + x;
            int win_y = y0 + y;
            if (win_x < 0 || win_x >= win_w || win_y < 0 || win_y >= win_h) continue;
            int tex_offset = y * tex->line_length + x * (tex->bpp / 8);
            int color = *(int *)(tex->addr + tex_offset);
            // Gestione trasparenza XPM: disegna solo i pixel con alpha 0 (visibili)
            if ((color & 0xFF000000) == 0xFF000000) continue;
            int base = get_pixel_color(&game->img, win_x, win_y);
            int blended = blend_color_alpha(base, color, alpha);
            ft_mlx_pixel_put(&game->img, win_x, win_y, blended);
        }
    }
}

// Overlay psichedelico trasparente su tutto lo schermo
void draw_trippy_overlay(t_game *game, int color)
{
    float alpha = 0.4f; // 40% overlay
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int base = get_pixel_color(&game->img, x, y);
            int blended = blend_color_alpha(base, color, alpha);
            ft_mlx_pixel_put(&game->img, x, y, blended);
        }
    }
}

void render_game(t_game *game)
{
    clear_image(&game->img, BLACK);
    raycast_scene(game);
    draw_minimap(game);
    render_frame(game);
    // Applica il filtro trippy solo dopo il primo cambio beat
    if (next_beat_idx > 0)
        draw_trippy_overlay(game, trippy_color);
}

int game_loop(void *param)
{
    static int first = 1;
    static struct timeval t_first;
    if (first) {
        gettimeofday(&t_first, NULL);
        first = 0;
    }
    t_game *game = (t_game *)param;
    if (game->state == MENU)
    {
        show_menu(game);
        return (0);
    }
    if (game->state == WIN) {
        clear_image(&game->img, BLACK);
        render_game(game); // disegna lo sfondo
        draw_centered_alpha_texture(game, &game->txtrs.win_img, 0.7f);
        mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
        return (0);
    }
    if (game->state == LOOSE) {
        clear_image(&game->img, BLACK);
        render_game(game); // disegna lo sfondo
        draw_centered_alpha_texture(game, &game->txtrs.loose_img, 0.7f);
        mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
        return (0);
    }
    // --- LOGICA BEAT E COLORE ---
    struct timeval now;
    gettimeofday(&now, NULL);
    float time_since_start = (now.tv_sec - music_start_time.tv_sec) + (now.tv_usec - music_start_time.tv_usec) / 1000000.0f;
    if (next_beat_idx < num_beats && time_since_start >= beats[next_beat_idx]) {
        trippy_color = random_trippy_color();
        next_beat_idx++;
    }
    // --- LOGICA TIMER COUNTDOWN ---
    if (now.tv_sec - game->timer_last_update.tv_sec >= 1 && game->timer_seconds > 0) {
        game->timer_seconds--;
        game->timer_last_update = now;
    }
    // --- LOGICA VITTORIA/SCONFITTA ---
    int px = (int)game->player.x;
    int py = (int)game->player.y;
    int win_found = 0;
    int loose_found = 0;
    if (game->timer_seconds > 0) {
        for (int dy = -1; dy <= 1 && (!win_found && !loose_found); dy++) {
            for (int dx = -1; dx <= 1 && (!win_found && !loose_found); dx++) {
                if (dx == 0 && dy == 0) continue;
                int nx = px + dx;
                int ny = py + dy;
                if (ny >= 0 && nx >= 0 && game->map[ny] && nx < (int)ft_strlen(game->map[ny])) {
                    if (game->map[ny][nx] == '2') win_found = 1;
                    if (game->map[ny][nx] == '3') loose_found = 1;
                }
            }
        }
    }
    if (game->timer_seconds > 0 && win_found) {
        game->state = WIN;
        if (game->music_pid > 0) { kill(game->music_pid, SIGTERM); waitpid(game->music_pid, NULL, 0); }
        game->music_pid = fork();
        if (game->music_pid == 0) {
            execlp("aplay", "aplay", "wav/Victory.wav", NULL);
            exit(1);
        }
        return (0);
    }
    if (game->timer_seconds > 0 && loose_found) {
        game->state = LOOSE;
        if (game->music_pid > 0) { kill(game->music_pid, SIGTERM); waitpid(game->music_pid, NULL, 0); }
        game->music_pid = fork();
        if (game->music_pid == 0) {
            execlp("aplay", "aplay", "wav/Game_Over.wav", NULL);
            exit(1);
        }
        return (0);
    }
    if (game->timer_seconds <= 0 && !win_found) {
        game->state = LOOSE;
        if (game->music_pid > 0) { kill(game->music_pid, SIGTERM); waitpid(game->music_pid, NULL, 0); }
        game->music_pid = fork();
        if (game->music_pid == 0) {
            execlp("aplay", "aplay", "wav/Game_Over.wav", NULL);
            exit(1);
        }
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


