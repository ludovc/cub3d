/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 cub3d.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lucasu <lucasu@student.42firenze.it>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/11 16:00:39 by lucasu			   #+#	  #+#			  */
/*	 Updated: 2025/11/11 16:03:20 by lucasu			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


float beats[MAX_BEATS];
int num_beats = 0;
int next_beat_idx = 0;
struct timeval music_start_time;
int trippy_color = 0x80FF00FF; // default

int random_trippy_color() {
    int a = 0x80 << 24; // alpha 50%
    int palette[] = {0xFF00FF, 0x00FFFF, 0xFFFF00, 0x39FF14, 0xFF0000, 0x00FF00, 0x0000FF, 0xFF8800};
    int idx = rand() % (sizeof(palette)/sizeof(palette[0]));
    return a | palette[idx];
}

void load_beats(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return;
    num_beats = 0;
    while (num_beats < MAX_BEATS && fscanf(f, "%f", &beats[num_beats]) == 1)
        num_beats++;
    fclose(f);
}

void start_music_and_timer() {
    gettimeofday(&music_start_time, NULL);
    next_beat_idx = 0;
    trippy_color = random_trippy_color();
    load_beats("wav/tempo.txt");
    int pid = fork();
    if (pid == 0) {
        execlp("aplay", "aplay", "wav/hospital.wav", NULL);
        exit(1);
    }
}

void update_trippy_color() {
    struct timeval now;
    gettimeofday(&now, NULL);
    float time_since_start = (now.tv_sec - music_start_time.tv_sec) + (now.tv_usec - music_start_time.tv_usec) / 1000000.0f;
    if (next_beat_idx < num_beats && time_since_start >= beats[next_beat_idx]) {
        trippy_color = random_trippy_color();
        next_beat_idx++;
    }
}

static void	initialization(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	
	init_image(game);
	game->state = MENU;

	game->keys.w_pressed = 0;
	game->keys.a_pressed = 0;
	game->keys.s_pressed = 0;
	game->keys.d_pressed = 0;
	game->keys.left_pressed = 0;
	game->keys.right_pressed = 0;
	// --- INIZIALIZZA TIMER COUNTDOWN ---
	game->timer_seconds = 162;
	gettimeofday(&game->timer_last_update, NULL);
}

void	free_all(t_game *game)
{
	if (game->settings)
		free_settings(game->settings);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->menu_img.img)
		mlx_destroy_image(game->mlx, game->menu_img.img);
	if (game->music_pid > 0)
	{
		kill(game->music_pid, SIGTERM);
		waitpid(game->music_pid, NULL, 0);
	}
	if (game->txtrs.n_wall.img) mlx_destroy_image(game->mlx, game->txtrs.n_wall.img);
	if (game->txtrs.s_wall.img) mlx_destroy_image(game->mlx, game->txtrs.s_wall.img);
	if (game->txtrs.e_wall.img) mlx_destroy_image(game->mlx, game->txtrs.e_wall.img);
	if (game->txtrs.w_wall.img) mlx_destroy_image(game->mlx, game->txtrs.w_wall.img);
	free_strarr(game->map);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void soundtrack(t_game *game)
{
    gettimeofday(&music_start_time, NULL);
    next_beat_idx = 0;
    srand(time(NULL));
    load_beats("wav/tempo.txt");
    trippy_color = random_trippy_color();
    game->music_pid = fork();
    if (game->music_pid == 0)
    {
        execlp("aplay", "aplay", "wav/hospital.wav", NULL);
        exit(1);
    }
}

int	main()
{
	t_game game;
    struct timeval t0, t1, t2, t3, t4;

    gettimeofday(&t0, NULL);


    parsing(&game);
    gettimeofday(&t1, NULL);


    initialization(&game);
    gettimeofday(&t2, NULL);


    load_textures(&game);
    gettimeofday(&t3, NULL);


    spawn_player(&game);
    gettimeofday(&t4, NULL);


	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game); 
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);

	free_all(&game);
}

