#include "../inc/cub3d.h"

void draw_h_edge(t_img *img, int x0, int y0, int color)
{
  int x;
  int y;

  y = 0;
  while (y < MINIMAP_WALL_THICKNESS)
  {
    x = 0;
    while (x < MINIMAP_TILE_SIZE)
    {
      ft_mlx_pixel_put(img, x0 + x, y0 + y, color);
      x++;
    }
    y++;
  }
}

void draw_v_edge(t_img *img, int x0, int y0, int color)
{
  int x;
  int y;

  x = 0;
  while (x < MINIMAP_WALL_THICKNESS)
  {
    y = 0;
    while (y < MINIMAP_TILE_SIZE)
    {
      ft_mlx_pixel_put(img, x0 + x, y0 + y, color);
      y++;
    }
    x++;
  }
}
