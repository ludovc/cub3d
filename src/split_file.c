#include "../inc/cub3d.h"

void	print_splitted_file(char **settings, char **map)
{
	printf("---------\n");
	print_strarr(settings);
	printf("---------\n");
	print_strarr(map);
	printf("---------\n");
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	is_map(char *str)
{
	int		i;

	i = 0;
	i = skip_spaces(str);
	if (str[i] == '1')
		return (1);
	else
		return (0);
}

int	arr_size_settings(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] && !is_map(arr[i]))
	{
		i++;
	}
	return (i);
}

int split_file(char **arr, char ***settings, char ***map)
{
    int settings_size;

    settings_size = arr_size_settings(arr);
    *settings = extract_settings_section(arr, settings_size);
    if (!*settings)
        return (0);
    *map = extract_map_section(arr, settings_size);
    if (!*map)
    {
        free_strarr(*settings);
        *settings = NULL;
        return (0);
    }
    return (1);
}
