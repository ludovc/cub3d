#include "../inc/cub3d.h"

// file preso dal mio so_long, e riadattato leggermente

char	*ft_strjoin_fs1(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

int	get_r(char *path)
{
	int		fd;
	char	*row;
	int		res;

	fd = open(path, O_RDONLY);
	res = 0;
	row = ft_get_next_line(fd);
	free(row);
	res++;
	while (row)
	{
		row = ft_get_next_line(fd);
		free(row);
		res++;
	}
	close(fd);
	return (res);
}

int	ensure_newline(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (map && !map[i])
		return (1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!map[i + 1] && map[i][j + 1] == '\0' && map[i][j] != '\n')
			{
				map[i] = ft_strjoin_fs1(map[i], "\n");
			}
			j++;
		}
		i++;
	}
	return (0);
}

// carica il file in un array di stringhe
char	**get_file(char *path)
{
	char	**map;
	char	*row;
	int		r;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	r = get_r(path);
	map = (char **) malloc((r + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < r)
	{
		row = ft_get_next_line(fd);
		map[i] = row;
		i++;
	}
	map[i] = NULL;
	close(fd);
	if (ensure_newline(map) == 1)
	{
		free(map);
		map = NULL;
	}
	return (map);
}
