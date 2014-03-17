/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 14:10:01 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 14:10:45 by flime            ###   ########.fr       */
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
void	buil_cd(int ac, char **msh_av, char **env, int opt_end, char *opt);
void	buil_env(int ac, char **msh_av, char **env, int opt_end);
char	**buil_setenv(int ac, char **msh_av, char **env);
char	**buil_unsetenv(int msh_ac, char **msh_av, char **env);

char	*env_chkname(char *s);
char	*env_rmname(char **env, char *env_name);

char	**buil(int ac, char **msh_av, char **env);

/*
** opt.c
*/
char	opt_chk(char *av, char *cmd_name, char *option, char *usage);
char	*opt_get(char **av);
int		opt_end(char **av/*, char *option*/);

void	ft_puttab(char **s);
int		ft_tablen(char **s);
int		ft_tabidx(char **t, char *s, int len);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strunion(char *av);
char	**ft_strsplit_space(char const *s);
int		ft_isspace(int c);

int		parse_tilde(char **s, char **env);

#endif /* !BUIL_H */
