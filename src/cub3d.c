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

char	**get_map(char *path);

void	print_splitted_file(char **settings, char **map)
{
	printf("---------\n");
	print_strarr(settings);
	printf("---------\n");
	print_strarr(map);
	printf("---------\n");
}

void	parsing()
{
	char	**settings;
	char	**map;
	char	**file;
	t_settings	*a;

	file = get_file("./maps/scene1.cub");
	split_file(file, &settings, &map);
	// print_splitted_file(settings, map);
	a = extract_settings(settings);
	printf("%p\n", a);
	print_strarr(settings);
	// print_settings(a);
	// check_settings();
	// check_leftovers();

	if (validate_map(map))
	{
		ft_printf("MAPPA INVALIDA\n");
		// controlla i free ed esci
		exit(1);
	}
	ft_printf("MAPPA BUONA\n");
}

int	main()
{
	t_game game;

	parsing();

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "CUB3D");
	game.player.x = WIDTH / 2;
	game.player.y = HEIGHT / 2;
	game.player.color = GREEN;
	
	draw_player(game.mlx, game.win, &game.player);

	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_hook(game.win, 2, 1, handle_key, &game);
	mlx_loop(game.mlx);
}
