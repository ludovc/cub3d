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

#include "minilibx/mlx.h"
#include <stdlib.h>

#define ESC_KEY 65307

typedef struct s_player {
	int x;
	int y;
	int color;
} t_player;

int	close_window()
{
	exit(0);
	return (0);
}

int handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == ESC_KEY)
		close_window();
    return (0);
}

void draw_player(void *mlx_ptr, void *win_ptr, t_player *player)
{
    int i;
	int j;


	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, player->x + i, player->y + j, player->color);
			j++;
		}
		i++;
	}
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_player player;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "titolo");
	player.x = 100;
	player.y = 100;
	player.color = 0x39FF14;
	draw_player(mlx, mlx_win, &player);

	mlx_hook(mlx_win, 17, 0, close_window, NULL);
	mlx_hook(mlx_win, 2, 1, handle_key, NULL);
	mlx_loop(mlx);
}
