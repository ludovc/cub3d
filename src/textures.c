#include "../inc/cub3d.h"

// Carica tutte le texture XPM
int load_textures(t_game *game)
{
    int w;
    int h;

    game->txtrs.n_wall.img = mlx_xpm_file_to_image(game->mlx, NORTH_WALL, &w, &h);
    game->txtrs.n_wall.addr = mlx_get_data_addr(game->txtrs.n_wall.img, \
        &game->txtrs.n_wall.bpp, &game->txtrs.n_wall.line_length, &game->txtrs.n_wall.endian);
    game->txtrs.s_wall.img = mlx_xpm_file_to_image(game->mlx, SOUTH_WALL, &w, &h);
    game->txtrs.s_wall.addr = mlx_get_data_addr(game->txtrs.s_wall.img, \
        &game->txtrs.s_wall.bpp, &game->txtrs.s_wall.line_length, &game->txtrs.s_wall.endian);
    game->txtrs.e_wall.img = mlx_xpm_file_to_image(game->mlx, EAST_WALL, &w, &h);
    game->txtrs.e_wall.addr = mlx_get_data_addr(game->txtrs.e_wall.img, \
        &game->txtrs.e_wall.bpp, &game->txtrs.e_wall.line_length, &game->txtrs.e_wall.endian);
    game->txtrs.w_wall.img = mlx_xpm_file_to_image(game->mlx, WEST_WALL, &w, &h);
    game->txtrs.w_wall.addr = mlx_get_data_addr(game->txtrs.w_wall.img, \
        &game->txtrs.w_wall.bpp, &game->txtrs.w_wall.line_length, &game->txtrs.w_wall.endian);

    if (!game->txtrs.n_wall.img || !game->txtrs.s_wall.img || !game->txtrs.e_wall.img || !game->txtrs.w_wall.img)
        return (0);

    return (1);
}

void draw_wall_texture(t_game *game, t_img *wall_tex, int screen_x, int draw_start, int draw_end, double wall_x)
{
    int y, tex_x, tex_y, line_height = draw_end - draw_start;
    tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= TEXTURE_WIDTH) tex_x = TEXTURE_WIDTH - 1;
    for (y = draw_start; y < draw_end; y++) {
        int d = y * 256 - HEIGHT * 128 + line_height * 128;
        tex_y = ((d * TEXTURE_HEIGHT) / line_height) / 256;
        if (tex_y < 0 || tex_y >= TEXTURE_HEIGHT) {
            continue;
        }
        if (!wall_tex || !wall_tex->addr) {
            continue;
        }
        int pixel = *(int *)(wall_tex->addr + (tex_y * wall_tex->line_length + tex_x * (wall_tex->bpp / 8)));
        ft_mlx_pixel_put(&game->img, screen_x, y, pixel);
    }
}

// Utility: converte una stringa RGB (es: "220,100,0") in un int colore 0xRRGGBB
int rgb_string_to_int(const char *rgb_str) {
    int r = 0, g = 0, b = 0;
    if (!rgb_str) return 0;
    sscanf(rgb_str, "%d,%d,%d", &r, &g, &b);
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}


void draw_ceiling(t_game *game) {
    int x, y;
    int color = rgb_string_to_int(game->settings->c);
    for (y = 0; y < HEIGHT / 2; y++) {
        for (x = 0; x < WIDTH; x++) {
            ft_mlx_pixel_put(&game->img, x, y, color);
        }
    }
}


void draw_floor(t_game *game) {
    int x, y;
    int color = rgb_string_to_int(game->settings->f);
    for (y = HEIGHT / 2; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            ft_mlx_pixel_put(&game->img, x, y, color);
        }
    }
}
