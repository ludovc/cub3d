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

void	remove_newline(char *str)
{
	char	*newline_point;

	if (!str)
		return ;
	newline_point = ft_strchr(str, '\n');
	if (newline_point)
		*newline_point = '\0';
}

// carica il file in un array di stringhe
char	**get_file(char *path)
{
	char	**file;
	char	*row;
	int		number_row;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	number_row = get_r(path);
	file = (char **) malloc((number_row + 1) * sizeof(char *));
	if (!file)
		return (NULL);
	i = 0;
	while (i < number_row)
	{
		row = ft_get_next_line(fd);
		remove_newline(row);
		file[i] = row;
		i++;
	}
	file[i] = NULL;
	close(fd);
	return (file);
}
