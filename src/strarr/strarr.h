#ifndef STRARR_H
# define STRARR_H

void	free_strarr(char **strarr);
void	print_strarr(char **arr);
void	strarr_append(char ***arr, char *new_str);
char	**strarr_dup(char **arr);
void	strarr_remove(char **arr, char *str);

#endif
