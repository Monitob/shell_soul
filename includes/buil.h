/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 14:10:01 by flime             #+#    #+#             */
/*   Updated: 2014/03/26 19:14:39 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUIL_H
# define BUIL_H

/*
** env_swap.c
*/

void	env_swap(char **env1, char **env2, char c);

/*
**  buil_cd.c
*/

void	buil_cmd(const char *path, char **msh_av, char **env);
void	buil_cd_home(char **av, char **env, int opt_end, int opt_p);
void	buil_cd_swap(char **av, char **env, int opt_end, int opt_p);
void	buil_cd(int ac, char **msh_av, char **env, char *opt);
void	buil_env(int ac, char **msh_av, char **env, int opt_end);
char	**buil_setenv(int ac, char **msh_av, char **env);
char	**buil_unsetenv(int msh_ac, char **msh_av, char **env);
char	*env_chkname(char *s);
char	*env_rmname(char **env, char *env_name);
char	opt_chk(char *av, char *cmd_name, char *option, char *usage);
char	*opt_get(char **av);
int		opt_end(char **av);
void	ft_puttab(char **s);
int		ft_tablen(char **s);
int		ft_tabidx(char **t, char *s, int len);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strunion(char *av);
char	**ft_strsplit_space(char const *s);
int		ft_isspace(int c);
int		parse_tilde(char **s, char **env);

#endif /* !BUIL_H */
