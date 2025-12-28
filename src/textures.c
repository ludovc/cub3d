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
    
    load_menu_image(game);

    if (!game->txtrs.n_wall.img || !game->txtrs.s_wall.img || !game->txtrs.e_wall.img || !game->txtrs.w_wall.img)
        return (0);

    return (1);
}

void draw_wall_texture(t_game *game, t_img *wall_tex, int screen_x, int draw_start, int draw_end, double wall_x)
{
    int y;
    int tex_x;
    int tex_y;
    int line_height;
    int d;
    int pixel;
    
    line_height = draw_end - draw_start;
    tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= TEXTURE_WIDTH) tex_x = TEXTURE_WIDTH - 1;
    y = draw_start;
    while (y < draw_end) {
        d = y * 256 - HEIGHT * 128 + line_height * 128;
        tex_y = ((d * TEXTURE_HEIGHT) / line_height) / 256;
        if (tex_y < 0 || tex_y >= TEXTURE_HEIGHT) {
            y++;
            continue;
        }
        if (!wall_tex || !wall_tex->addr) {
            y++;
            continue;
        }
        pixel = *(int *)(wall_tex->addr + (tex_y * wall_tex->line_length + tex_x * (wall_tex->bpp / 8)));
        ft_mlx_pixel_put(&game->img, screen_x, y, pixel);
        y++;
    }
}

// Utility: converte una stringa RGB (es: "220,100,0") in un int colore 0xRRGGBB usando solo funzioni della libft
int rgb_string_to_int(const char *rgb_str)
{
    int     i;
    int     r;
    int     g;
    int     b;
    char    **split;

    r = 0;
    g = 0;
    b = 0;
    if (!rgb_str)
        return 0;
    split = ft_split(rgb_str, ',');
    if (split)
    {
        if (split[0]) r = ft_atoi(split[0]);
        if (split[1]) g = ft_atoi(split[1]);
        if (split[2]) b = ft_atoi(split[2]);
        i = 0;
        while (split[i])
            free(split[i++]);
        free(split);
    }
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
