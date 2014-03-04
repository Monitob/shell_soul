#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);;
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putstr(const char *s);
void	ft_putstr_fd(const char *s,int fd);
void	ft_putendl(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *s1, const char *s2);
int		ft_atoi(const char *str);
int		ft_isdigit(char c);
char	**ft_strsplit(const char *str, char c);
int		nb_split(const char *str, char c);
int		is_space(char c);
int		is_sep(char c);
int		is_sep_space(char c);

#endif /* !FT_STRINGS_H */
