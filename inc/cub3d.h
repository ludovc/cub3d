#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include "../minilibx/mlx.h"
#include "../inc/libft.h"

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

typedef struct s_dimensions {
	int width;
	int height;
} t_dimensions;

typedef struct s_objects {
	int fd;
} t_objects;

typedef struct s_game {
	void *mlx;
	void *win;
	t_player player;
	char **map;
	char **scene;
} t_game;

// mlx_hook.c
int	close_window();
int handle_key(int keycode, void *param);

// mlx_draw.c
void move_player(t_player *player, int dx, int dy);
void draw_player(void *mlx_ptr, void *win_ptr, t_player *player);
void clear_player(void *mlx_ptr, void *win_ptr, t_player *player);
void update_player(t_game *game, int dx, int dy);

// cub_parse.c
int parse(int argc, char *argv[]);
t_game setup_game(char *scene_file, t_dimensions *d);
int check_usage_and_file_type(int argc, char *map_file);
int validate_map_file(char *map_file);
int check_map_line_lengths(int fd);
int validate_line_lengths(int fd, size_t line_length);

// Functions referenced but not implemented yet
int is_playable(char *map_file);
int check_map_objects(char *map_file);
t_dimensions get_map_dimensions(char *scene_file);
char **create_map(char *scene_file);

char	**get_file(char *path);
void	print_strarr(char **arr);
void	split_file(char **arr, char ***settings, char ***map);

#endif
