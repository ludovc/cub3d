#include "../inc/cub3d.h"
/*
** Questa funzione permette di disegnare direttamente un singolo pixel in una struttura immagine (t_img)
** a una posizione specifica (x, y) e con un determinato colore. È pensata per lavorare con immagini
** create tramite la MiniLibX, una piccola libreria grafica usata spesso nei progetti 42.
**
** Parametri:
**   - t_img *img: puntatore alla struttura immagine che contiene i dati del buffer grafico,
**                 l'indirizzo di memoria dove sono memorizzati i pixel, la lunghezza di ogni riga,
**                 il numero di bit per pixel e l'endianess.
**   - int x, y: coordinate del pixel da modificare all'interno dell'immagine.
**   - int color: valore numerico che rappresenta il colore da assegnare al pixel (di solito in formato 0xRRGGBB).
**
** Funzionamento:
** 1. Per evitare scritture fuori dal buffer che potrebbero causare crash o corruzione di memoria, bisogna fare il controllo dei limiti: 
**    la funzione verifica che le coordinate x e y siano all'interno dei limiti dell'immagine (WIDTH e HEIGHT). 
**    Se il pixel richiesto è fuori dai limiti, la funzione termina subito senza modificare nulla.
**
** 2. Calcolo dell'indirizzo del pixel: viene calcolato l'indirizzo di memoria esatto dove si trova il pixel da modificare.
**    Questo si ottiene sommando all'indirizzo base dell'immagine (img->addr) uno spostamento calcolato così:
**      - y * img->line_length: sposta il puntatore all'inizio della riga y-esima (ogni riga può avere un padding).
**      - x * (img->bits_per_pixel / 8): sposta il puntatore alla colonna x-esima, tenendo conto di quanti byte occupa ogni pixel.
**
** 3. Scrittura del colore: l'indirizzo calcolato viene castato a (unsigned int*) e viene scritto il valore del colore.
**    In questo modo il pixel nella posizione (x, y) dell'immagine assumerà il colore desiderato.
**
** Note:
** - Questa funzione permette di manipolare direttamente i pixel dell'immagine, rendendo possibile la creazione di
**   primitive grafiche personalizzate (linee, rettangoli, cerchi, ecc.) senza dover usare funzioni di alto livello.
** - È importante che l'immagine sia stata inizializzata correttamente e che i parametri della struttura t_img siano validi.
*/

void ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel;
    int color = 0;
    if (!img || !img->addr) return 0;
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    if (img->endian == 0) // little endian
        color = *(int *)pixel;
    else // big endian
        color = ((unsigned char)pixel[2] << 16) | ((unsigned char)pixel[1] << 8) | (unsigned char)pixel[0];
    return color;
}


void move_player(t_game *game, float dx, float dy)
{
    float new_x = game->player.x + dx * MOVE_SPEED;
    float new_y = game->player.y + dy * MOVE_SPEED;
    
    // Collision detection
    if (is_walkable(game->map, (int)new_x, (int)new_y))
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

int is_walkable(char **map, int x, int y)
{
    if (x < 0 || y < 0)
        return (0);
    if (!map[y] || !map[y][x])
        return (0);
    return (map[y][x] == '0' || is_spawn(map[y][x]));
}

void draw_player(t_img *img, t_player *player)
{
    int i;
    int j;
    int screen_x, screen_y;
    
    // Converti coordinate mappa in coordinate schermo minimap
    screen_x = MINIMAP_OFFSET_X + (int)(player->x * MINIMAP_TILE_SIZE) - 1;
    screen_y = MINIMAP_OFFSET_Y + (int)(player->y * MINIMAP_TILE_SIZE) - 1;

    i = 0;
    while (i < PLAYER_SIZE)
    {
        j = 0;
        while (j < PLAYER_SIZE)
        {
            ft_mlx_pixel_put(img, screen_x + i, screen_y + j, player->color);
            j++;
        }
        i++;
    }
}

void update_player(t_game *game, int dx, int dy)
{
    // salvo la posizione precedente per ottimizzare il redraw
    float old_x = game->player.x;
    float old_y = game->player.y;
    
    move_player(game, dx, dy);
    
    if (old_x != game->player.x || old_y != game->player.y)
        render_game(game);

}
