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

int	is_file(char *str)
{
	if (open(str, O_RDONLY) == -1)
		return (0);
	else
		return (1);
}

int	count_char(char *str, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	is_full_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_rgb(char *str)
{
	char	**parts;
	int		res;

	if (count_char(str, ',') != 2)
		return (0);
	res = 1;
	parts = ft_split(str, ',');
	if (strarr_len(parts) != 3)
	{
		res = 0;
	}
	else
	{
		if (!is_full_digit_string(parts[0]) || !is_full_digit_string(parts[1]) || !is_full_digit_string(parts[2]))
			res = 0;
		else if (ft_atoi(parts[0]) > 255)
			res = 0;
		else if (ft_atoi(parts[1]) > 255)
			res = 0;
		else if (ft_atoi(parts[2]) > 255)
			res = 0;
	}
	free_strarr(parts);
	return (res);
}

int	check_settings(t_settings *settings)
{
	if (!is_file(settings->no))
		return (0);
	if (!is_file(settings->so))
		return (0);
	if (!is_file(settings->we))
		return (0);
	if (!is_file(settings->ea))
		return (0);
	if (!is_rgb(settings->f))
		return (0);
	if (!is_rgb(settings->c))
		return (0);
	return (1);
}

void	parsing(t_game *game)
{
	char	**settings;
	char	**map;
	char	**file;

	file = get_file("./maps/scene1.cub");
	// print_strarr(file);
	split_file(file, &settings, &map);
	free_strarr(file);
	game->settings = extract_settings(settings);
	if (!game->settings)
	{
		ft_printf("Settings invalide\n");
	}
	if (check_settings(game->settings) == 0)
		ft_printf("Settings invalide\n");
	// check_leftovers();
	free_strarr(settings);

	if (validate_map(map))
		ft_printf("MAPPA INVALIDA\n");
	else
		ft_printf("MAPPA BUONA\n");
	free_strarr(map);
}

void	free_all(t_game *game)
{
	free_settings(game->settings);
}

int	main()
{
	t_game game;

	parsing(&game);

	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "CUB3D");
	// game.player.x = WIDTH / 2;
	// game.player.y = HEIGHT / 2;
	// game.player.color = GREEN;
	
	// draw_player(game.mlx, game.win, &game.player);

	// mlx_hook(game.win, 17, 0, close_window, NULL);
	// mlx_hook(game.win, 2, 1, handle_key, &game);
	// mlx_loop(game.mlx);
	free_all(&game);
}
