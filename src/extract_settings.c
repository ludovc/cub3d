#include "../inc/cub3d.h"

void	free_settings(t_settings *a)
{
	free(a->no);
	free(a->so);
	free(a->we);
	free(a->ea);
	free(a->f);
	free(a->c);
	free(a);
}

void	print_settings(t_settings *a)
{
	printf("NO: %s\n", a->no);
	printf("SO: %s\n", a->so);
	printf("WE: %s\n", a->we);
	printf("EA: %s\n", a->ea);
	printf("F: %s\n", a->f);
	printf("C: %s\n", a->c);
}

char	*right_part(char *str)
{
	char	*res;
	char	**str_parts;

	res = NULL;
	if (str[0] == ' ')
		return (NULL);
	str_parts = ft_split(str, ' ');
	res = ft_strdup(str_parts[0]);
	free_strarr(str_parts);
	return (res);
}

char	*strarr_find_varcontent(char **arr, char *var_name)
{
	int		i;
	char	**str_parts;
	char	*res;

	i = 0;
	while (arr[i])
	{
		str_parts = ft_split(arr[i], ' ');
		if (str_parts[0] && ft_strcmp(str_parts[0], var_name) == 0)
		{
			if (str_parts[1] == NULL)
				res = ft_strdup("");
			else
				res = ft_strdup(str_parts[1]);
			free_strarr(str_parts);
			return (res);
		}
		free_strarr(str_parts);
		i++;
	}
	return (NULL);
}

char	*strarr_pop(char **strarr, char *var)
{
	char	*var_content;

	var_content = strarr_find_varcontent(strarr, var);
	strarr_remove_var(strarr, var);
	return (var_content);
}

t_settings	*extract_settings(char **settings)
{
	t_settings	*a;

	a = malloc(sizeof(t_settings));

	a->no = strarr_pop(settings, "NO");
	a->so = strarr_pop(settings, "SO");
	a->we = strarr_pop(settings, "WE");
	a->ea = strarr_pop(settings, "EA");
	a->f = strarr_pop(settings, "F");
	a->c = strarr_pop(settings, "C");

	if (!a->no || !a->so || !a->we || !a->ea || !a->f || !a->c)
	{
		free_settings(a);
		return (NULL);
	}
	else
		return (a);
}
