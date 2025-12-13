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

#define WIDTH 1080
#define HEIGHT 720

#define BLACK 0x000000
#define GREEN 0x39FF14
#define RED 0xFF0000
#define YELLOW 0xFFFF00

#define MINIMAP_OFFSET_X 30
#define MINIMAP_OFFSET_Y (HEIGHT - 200)
#define MINIMAP_WALL_FILL_COLOR 0x555555
#define MINIMAP_TILE_SIZE 12
#define MINIMAP_WALL_THICKNESS 1

#define MOVE_SPEED 0.05f
#define PLAYER_SIZE 4



typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_player {
	float x;
	float y;
	int color;
} t_player;

typedef struct s_dimensions {
	int width;
	int height;
} t_dimensions;

typedef struct s_objects {
	int fd;
} t_objects;

typedef struct s_settings
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_settings;

typedef struct s_keys {
	int w_pressed;
	int a_pressed;
	int s_pressed;
	int d_pressed;
} t_keys;

typedef struct s_game {
	void *mlx;
	void *win;
	t_img img;
	t_player player;
	char **map;
	char **scene;
	t_settings	*settings;
	t_keys keys;
} t_game;

// mlx_hook.c
int	close_window();
int handle_keypress(int keycode, void *param);
int handle_keyrelease(int keycode, void *param);
int game_loop(void *param);

// cub3d.c
void initialization(t_game *game);

// mlx_draw.c
void move_player(t_game *game, float dx, float dy);
int is_walkable(char **map, int x, int y);
void draw_player(t_img *img, t_player *player);
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
int	split_file(char **arr, char ***settings, char ***map);
#include "../src/strarr/strarr.h"

// extract_settings.c
t_settings	*extract_settings(char **settings);

// extract .cub section.c
// ho modificato settings.c per usare queste due al fine di normalizzare la mappa
char **extract_settings_section(char **arr, int settings_size);
char **extract_map_section(char **arr, int start_idx);

// parse map
int	validate_map(char **map);
int is_valid_tile(char c);
int is_spawn(char c);
int find_player_spawn(char **map, float *x, float *y);
int	map_height(char **map);
int	map_max_width(char **map);
void normalize_map(char ***map);

void	free_settings(t_settings *a);
void	print_settings(t_settings *a);

// check_settings.c
int	check_settings(t_settings *settings);

// draw & normalize minimap
void ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void init_image(t_game *game);
void clear_image(t_img *img, int color);
void render_frame(t_game *game);
void draw_minimap(t_game *game);
void draw_minimap_dynamic(t_game *game);
void draw_h_edge(t_img *img, int x0, int y0, int color);
void draw_v_edge(t_img *img, int x0, int y0, int color);
int	get_map_max_width(char **arr, int start);
char *pad_line(char *line, int target_width);

#endif
