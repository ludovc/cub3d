#include "../inc/cub3d.h"

// Carica tutte le texture XPM
int load_textures(t_game *game)
{
    int w;
    int h;

    struct timeval t0, t1;
    gettimeofday(&t0, NULL);

    game->txtrs.n_wall.img = mlx_xpm_file_to_image(game->mlx, NORTH_WALL, &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.n_wall.width = w; game->txtrs.n_wall.height = h;
    game->txtrs.n_wall.addr = mlx_get_data_addr(game->txtrs.n_wall.img, \
        &game->txtrs.n_wall.bpp, &game->txtrs.n_wall.line_length, &game->txtrs.n_wall.endian);
    gettimeofday(&t0, NULL);

    game->txtrs.s_wall.img = mlx_xpm_file_to_image(game->mlx, SOUTH_WALL, &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.s_wall.width = w; game->txtrs.s_wall.height = h;
    game->txtrs.s_wall.addr = mlx_get_data_addr(game->txtrs.s_wall.img, \
        &game->txtrs.s_wall.bpp, &game->txtrs.s_wall.line_length, &game->txtrs.s_wall.endian);
    gettimeofday(&t0, NULL);

    game->txtrs.e_wall.img = mlx_xpm_file_to_image(game->mlx, EAST_WALL, &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.e_wall.width = w; game->txtrs.e_wall.height = h;
    game->txtrs.e_wall.addr = mlx_get_data_addr(game->txtrs.e_wall.img, \
        &game->txtrs.e_wall.bpp, &game->txtrs.e_wall.line_length, &game->txtrs.e_wall.endian);
    gettimeofday(&t0, NULL);

    game->txtrs.w_wall.img = mlx_xpm_file_to_image(game->mlx, WEST_WALL, &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.w_wall.width = w; game->txtrs.w_wall.height = h;
    game->txtrs.w_wall.addr = mlx_get_data_addr(game->txtrs.w_wall.img, \
        &game->txtrs.w_wall.bpp, &game->txtrs.w_wall.line_length, &game->txtrs.w_wall.endian);
    gettimeofday(&t0, NULL);

    game->txtrs.win_condition.img = mlx_xpm_file_to_image(game->mlx, "xpm/win_condition.xpm", &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.win_condition.width = w; game->txtrs.win_condition.height = h;
    game->txtrs.win_condition.addr = mlx_get_data_addr(game->txtrs.win_condition.img, \
        &game->txtrs.win_condition.bpp, &game->txtrs.win_condition.line_length, &game->txtrs.win_condition.endian);
    gettimeofday(&t0, NULL);

    game->txtrs.win_img.img = mlx_xpm_file_to_image(game->mlx, "xpm/win.xpm", &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.win_img.width = w; game->txtrs.win_img.height = h;
    game->txtrs.win_img.addr = mlx_get_data_addr(game->txtrs.win_img.img, \
        &game->txtrs.win_img.bpp, &game->txtrs.win_img.line_length, &game->txtrs.win_img.endian);
    gettimeofday(&t0, NULL);

    game->txtrs.loose_img.img = mlx_xpm_file_to_image(game->mlx, "xpm/loose.xpm", &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.loose_img.width = w; game->txtrs.loose_img.height = h;
    game->txtrs.loose_img.addr = mlx_get_data_addr(game->txtrs.loose_img.img, \
        &game->txtrs.loose_img.bpp, &game->txtrs.loose_img.line_length, &game->txtrs.loose_img.endian);
    gettimeofday(&t0, NULL);
    game->txtrs.loose_condition.img = mlx_xpm_file_to_image(game->mlx, "xpm/wall_loose_condition.xpm", &w, &h);
    gettimeofday(&t1, NULL);
    game->txtrs.loose_condition.width = w; game->txtrs.loose_condition.height = h;
    game->txtrs.loose_condition.addr = mlx_get_data_addr(game->txtrs.loose_condition.img, \
        &game->txtrs.loose_condition.bpp, &game->txtrs.loose_condition.line_length, &game->txtrs.loose_condition.endian);
    gettimeofday(&t0, NULL);
    load_menu_image(game);
    gettimeofday(&t1, NULL);
    
    if (!game->txtrs.n_wall.img || !game->txtrs.s_wall.img || !game->txtrs.e_wall.img || !game->txtrs.w_wall.img || !game->txtrs.win_condition.img || !game->txtrs.win_img.img || !game->txtrs.loose_img.img || !game->txtrs.loose_condition.img)
        return (0);

    return (1);
}

void draw_wall_texture(t_game *game, t_img *tex, int x,
                       int draw_start, int draw_end,
                       int line_height_full, double wall_x)
{
    int tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= TEXTURE_WIDTH) tex_x = TEXTURE_WIDTH - 1;

    if (!tex || !tex->addr) return;

    double step = 1.0 * TEXTURE_HEIGHT / (double)line_height_full;

    // tex_pos deve partire dalla y della texture corrispondente a draw_start
    // e deve “saltare” automaticamente la parte tagliata fuori schermo
    double tex_pos = (draw_start - HEIGHT / 2.0 + line_height_full / 2.0) * step;

    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos;
        tex_pos += step;

        if (tex_y < 0) tex_y = 0;
        if (tex_y >= TEXTURE_HEIGHT) tex_y = TEXTURE_HEIGHT - 1;

        int pixel = *(int *)(tex->addr
            + tex_y * tex->line_length
            + tex_x * (tex->bpp / 8));

        ft_mlx_pixel_put(&game->img, x, y, pixel);
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
