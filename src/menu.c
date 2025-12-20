#include "../inc/cub3d.h"

void load_menu_image(t_game *game)
{
    int w, h;
    game->menu_img.img = mlx_xpm_file_to_image(game->mlx, "xpm/menu.xpm", &w, &h);
    game->menu_img.addr = mlx_get_data_addr(game->menu_img.img, \
        &game->menu_img.bpp, &game->menu_img.line_length, &game->menu_img.endian);
}

void show_menu(t_game *game)
{
    if (game->menu_img.img)
        mlx_put_image_to_window(game->mlx, game->win, game->menu_img.img, 0, 0);
}

