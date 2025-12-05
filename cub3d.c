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

int	main()
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "titolo");
	mlx_hook(mlx_win, 17, 0, close_window, NULL);
	mlx_hook(mlx_win, 2, 1, handle_key, NULL);
	mlx_loop(mlx);
}
