#include "../inc/cub3d.h"

char **extract_settings_section(char **arr, int settings_size)
{
    char    **res;
    int     i;

    res = malloc(sizeof(char *) * (settings_size + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (i < settings_size)
    {
        res[i] = ft_strdup(arr[i]);
        if (!res[i])
        {
            free_strarr(res);
            return (NULL);
        }
        i++;
    }
    res[i] = NULL;
    return (res);
}

char **extract_map_section(char **arr, int start_idx)
{
    int     map_size;
    int     max_width;
    char    **res;
    int     i;

    map_size = strarr_len(arr) - start_idx;
    max_width = get_map_max_width(arr, start_idx);
    res = malloc(sizeof(char *) * (map_size + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (i < map_size)
    {
        res[i] = pad_line(arr[start_idx + i], max_width);
        if (!res[i])
        {
            free_strarr(res);
            return (NULL);
        }
        i++;
    }
    res[i] = NULL;
    return (res);
}
