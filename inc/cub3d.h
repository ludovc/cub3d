#ifndef CUB3D_H
# define CUB3D_H

#include "../minilibx/mlx.h"
#include "../inc/libft.h"

#include <signal.h>
#include <sys/wait.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define LEFT_ARROW_KEY 65361
#define RIGHT_ARROW_KEY 65363
#define ENTER_KEY 65293
#define SPACE_KEY 32

#define WIDTH 1080
#define HEIGHT 720

#define BLACK 0x000000
#define GREY 0x555555
#define GREEN 0x39FF14
#define RED 0xFF0000
#define YELLOW 0xFFFF00

#define MINIMAP_OFFSET_X 30
#define MINIMAP_OFFSET_Y (HEIGHT - 200)
#define MINIMAP_TILE_SIZE 12
#define MINIMAP_WALL_THICKNESS 1

#define MOVE_SPEED 0.1f
#define PLAYER_SIZE 4
#define CAMERA_ROTATION 0.05
#define TEXTURE_HEIGHT 641
#define TEXTURE_WIDTH 736

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define FOV (60.0 * M_PI / 180.0)

#define NORTH_WALL "xpm/wall.xpm"
#define SOUTH_WALL "xpm/wall.xpm"
#define EAST_WALL "xpm/wall-dark.xpm"
#define WEST_WALL "xpm/wall-dark.xpm"

#define MAX_BEATS 2048

typedef struct s_player {
    float x;
    float y;
    float angle; // direzione in radianti
    float dirx;
	float diry;
    float planex;
	float planey;
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
	int left_pressed;
	int right_pressed;
	int enter_pressed;
} t_keys;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp; // bits per pixel
	int		line_length;
	int		endian;
	int		width;
	int		height;
} t_img;

typedef struct s_textures {
    t_img n_wall;
    t_img s_wall;
    t_img e_wall;
    t_img w_wall;
    t_img win_condition; // texture speciale per tile '2'
    t_img win_img; // texture schermata vittoria
    t_img loose_img; // texture schermata sconfitta
    t_img loose_condition; // texture speciale per tile '3'
} t_textures;

typedef enum e_game_state {
    MENU,
    PLAYING,
    WIN,
    LOOSE
}   t_game_state;

typedef struct s_game {
    void *mlx;
    void *win;
    t_img img;
    t_player player;
    char **map;
    char **scene;
    t_settings   *settings;
    t_keys keys;
    int music_pid;
    t_textures txtrs;
    t_game_state state; // aggiunto stato del gioco
    t_img menu_img;     // aggiunto per menu.xpm
    int timer_seconds;           // secondi rimanenti per il countdown
    struct timeval timer_last_update; // per aggiornamento ogni secondo
} t_game;

typedef struct s_ray {
    double ray_dirx;
    double ray_diry;
    int mapx;
    int mapy;
    double delta_distx;
    double delta_disty;
    int step_x;
    int step_y;
    double side_distx;
    double side_disty;
    int side;
    double perp_dist;
    int line_h;
    int draw_start;
    int draw_end;
} t_ray;

typedef enum e_wall_dir {
    NORTH,
    SOUTH,
    EAST,
    WEST
}   t_wall_dir;

// mlx_hook.c
int	close_window();
int handle_keypress(int keycode, void *param);
int handle_keyrelease(int keycode, void *param);
int game_loop(void *param);


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
void	print_splitted_file(char **settings, char **map);
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
void spawn_player(t_game *game);
int	map_height(char **map);
int	map_max_width(char **map);
void normalize_map(char ***map);

void	free_settings(t_settings *a);
void	print_settings(t_settings *a);

// check_settings.c
int	check_settings(t_settings *settings);

int	parsing(t_game *game);

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

void	free_all(t_game *game);

void	render_game(t_game *game);
void set_player_dir(t_game *g);

int load_textures(t_game *game);
void draw_ceiling_texture(t_game *game, t_textures *txtrs);
void draw_floor_texture(t_game *game, t_textures *txtrs);
void draw_wall_texture(t_game *game, t_img *tex, int x, int draw_start, int draw_end, int line_height_full, double wall_x);

int rgb_string_to_int(const char *rgb_str);
void draw_ceiling(t_game *game);
void draw_floor(t_game *game);

void show_menu(t_game *game);
void load_menu_image(t_game *game);
int menu_key_handler(int keycode, t_game *game);
int is_in_menu(void);

// Prototipi delle funzioni di gioco
int handle_keypress(int keycode, void *param);
int handle_keyrelease(int keycode, void *param);
int game_loop(void *param);
void soundtrack(t_game *game);
void	reset_keys(t_keys *keys);

#define MAX_BEATS 2048
extern float beats[MAX_BEATS];
extern int num_beats;
extern int next_beat_idx;
extern struct timeval music_start_time;
extern int trippy_color;
int random_trippy_color(void);
int get_pixel_color(t_img *img, int x, int y);

#endif
