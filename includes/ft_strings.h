/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:15:20 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:15:27 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

# include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putchar(const char c);
void	ft_putstr(const char *s);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strcat_redi(char *str1, char *str2);
int		ft_atoi(const char *str);
int		ft_isdigit(char c);
char	**ft_strsplit(const char *str, char c);
int		nb_split(const char *str, char c);
int		is_space(char c);
int		is_sep(char c);
int		is_sep_space(char c);

int		ft_error(char *err_msg);
void	*ft_error_null(char *err_msg);
int		ft_error_parsing(char *err_msg);
char	*ft_strndup(char *str, int len);

#endif
