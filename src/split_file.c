#include "../inc/cub3d.h"

void	print_strarr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

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

void	split_file(char **arr, char ***settings, char ***map)
{
	int		i;
	int		size;
	int		size_new;
	char	**res;

	size = arr_size_settings(arr);
	res = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = NULL;
	*settings = res;
	size_new = strarr_len(arr) - size;
	res = malloc(sizeof(char *) * (size_new + 1));
	i = 0;
	while (i < size_new)
	{
		res[i] = ft_strdup(arr[size + i]);
		i++;
	}
	res[i] = NULL;
	*map = res;
}
