#include <stdlib.h>
#include "minilibx/mlx.h"

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

#define WIDTH 300
#define HEIGHT 200

#define BLACK 0x000000
#define GREEN 0x39FF14


typedef struct s_player {
	int x;
	int y;
	int color;
} t_player;

typedef struct s_game {
	void *mlx;
	void *win;
	t_player player;
} t_game;

// mlx_hook.c
int	close_window();
int handle_key(int keycode, void *param);

// mlx_draw.c
void move_player(t_player *player, int dx, int dy);
void draw_player(void *mlx_ptr, void *win_ptr, t_player *player);
void clear_player(void *mlx_ptr, void *win_ptr, t_player *player);
void update_player(t_game *game, int dx, int dy);   