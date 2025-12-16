# include "../inc/cub3d.h"

/*
**  Questa funzione inizializza la struttura immagine del gioco, creando una nuova immagine MLX
**  e ottenendo il puntatore al buffer dei pixel e le sue proprietà.
**  Parametri:
**    - t_game *game: puntatore alla struttura di gioco che contiene la struttura immagine (t_img).
**  Funzionamento:
**    1. Crea una nuova immagine MLX con le dimensioni specificate (WIDTH x HEIGHT) e assegna il puntatore all'immagine alla struttura t_img.
**    2. Ottiene l'indirizzo del buffer dei pixel dell'immagine, insieme alle proprietà come bits_per_pixel, line_length ed endianess,
**       e li memorizza nella struttura t_img.
*/  

void init_image(t_game *game)
{
    game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img, 
                                       &game->img.bits_per_pixel,
                                       &game->img.line_length, 
                                       &game->img.endian);
}

void clear_image(t_img *img, int color)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}

void render_frame(t_game *game)
{
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

static void fill_tile(t_img *img, int x0, int y0, int color)
{
  int x;
  int y;

  y = 0;
  while (y < MINIMAP_TILE_SIZE)
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

static char bounds_check(char **map, int y, int x)
{
	int row_len;
    if (y < 0 || x < 0)
		return ' ';
    if (!map || !map[y])
		return ' ';
    row_len = (int)ft_strlen(map[y]);
    if (x >= row_len)
		return ' ';
    return map[y][x];
}

static void draw_borders(t_game *g, int cx, int cy)
{
    int x0;
    int y0;
    int x1;
    int y1;

	x0 = MINIMAP_OFFSET_X + (cx * MINIMAP_TILE_SIZE);
	y0 = MINIMAP_OFFSET_Y + (cy * MINIMAP_TILE_SIZE);
	x1 = x0 + MINIMAP_TILE_SIZE;
	y1 = y0 + MINIMAP_TILE_SIZE;

	char up;
    char down;
    char left;
    char right;

	up = bounds_check(g->map, cy - 1, cx);
	down = bounds_check(g->map, cy + 1, cx);
	left = bounds_check(g->map, cy, cx - 1);
	right = bounds_check(g->map, cy, cx + 1);

    if (up == '0' || is_spawn(up))
		draw_h_edge(&g->img, x0, y0, GREEN);
    if (down == '0' || is_spawn(down))
		draw_h_edge(&g->img, x0, y1 - MINIMAP_WALL_THICKNESS, GREEN);
    if (left == '0' || is_spawn(left))
		draw_v_edge(&g->img, x0, y0, GREEN);
    if (right == '0' || is_spawn(right))
		draw_v_edge(&g->img, x1 - MINIMAP_WALL_THICKNESS, y0, GREEN);
}

// Disegna tutto quello che deve essere renderizzato solo una volta (senza player)
void draw_minimap_static(t_game *game)
{
	int row_len;
	int x;
	int y;
	char c;

	if (!game || !game->map)
		return;

	clear_image(&game->img, BLACK);

	y = 0;
	while (game->map[y])
	{
		row_len = (int)ft_strlen(game->map[y]);
		x = 0;
		while (x < row_len)
		{
			c = game->map[y][x];
      if (c == '1' || c == ' ')
      {
        fill_tile(&game->img, 
                  MINIMAP_OFFSET_X + (x * MINIMAP_TILE_SIZE), 
                  MINIMAP_OFFSET_Y + (y * MINIMAP_TILE_SIZE), 
                  MINIMAP_WALL_FILL_COLOR);
        if (c == '1')
          draw_borders(game, x, y);
      }
			x++;
		}
		y++;
	}
}


/*
** Chiama draw_minimap_static per disegnare la mappa senza elementi dinamici.
** Sovrappone la posizione del player sulla minimappa tramite draw_player.
** Mostra il risultato finale nella finestra di gioco con render_frame.
** Questa funzione va chiamata ogni volta che si vuole aggiornare la minimappa a schermo.
*/
void draw_minimap(t_game *game)
{
    if (!game || !game->map)
        return;
        
    draw_minimap_static(game);
    draw_player(&game->img, &game->player);
    render_frame(game);
}