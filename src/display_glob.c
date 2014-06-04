/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_glob.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:47:08 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:34:42 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int		remove_path_name(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (str[i] == '/')
			return (i + 1);
		--i;
	}
	return (0);
}

int		get_max_cols(char **path, int nb)
{
	int	i;
	int	max_cols;

	i = 0;
	max_cols = 0;
	while (i < nb)
	{
		if ((int)(ft_strlen(path[i] + remove_path_name(path[i]))) > max_cols)
			max_cols = ft_strlen(path[i] + remove_path_name(path[i]));
		i++;
	}
	return (max_cols);
}

void	display_nice_glob(glob_t *pglob, t_win_size *win_size)
{
	unsigned int	i;
	char			*str;

	i = 0;
	while (i < pglob->gl_pathc)
	{
		str = pglob->gl_pathv[i] + remove_path_name(pglob->gl_pathv[i]);
		win_size->current_cols = ft_strlen(str);
		win_size->current_line_cols += win_size->max_cols;
		if (win_size->current_line_cols + 1 > win_size->cols)
		{
			win_size->current_line_cols = win_size->max_cols;
			ft_putchar('\n');
		}
		ft_putstr(pglob->gl_pathv[i] + remove_path_name(pglob->gl_pathv[i]));
		i++;
		while (win_size->current_cols - 1 < win_size->max_cols)
		{
			ft_putchar(' ');
			win_size->current_cols++;
		}
	}
	ft_putchar('\n');
}

int		check_nbr_aff(glob_t *pglob)
{
	char	buf;
	int		ret;

	if (pglob->gl_pathc > 50)
	{
		ft_putstr("Really want to display this ? (lots of stuff)\n");
		ret = read(0, &buf, 1);
		if (ret == -1)
			return (ft_error("Couldn't read choice\n"));
		ft_putchar('\n');
		if (buf == 'y' || buf == 'Y')
			return (1);
		return (0);
	}
	else
		return (1);
}

int		display_glob(glob_t *pglob)
{
	t_win_size		win_size;
	struct winsize	size_term;

	if (ioctl(0, TIOCGWINSZ, (char*)&size_term) < 0)
		return (ft_error("Error in ioctl --> globbing\n"));
	win_size.current_line_cols = 0;
	win_size.cols = size_term.ws_col;
	win_size.max_cols = get_max_cols(pglob->gl_pathv, pglob->gl_pathc);
	if (check_nbr_aff(pglob))
		display_nice_glob(pglob, &win_size);
	if (pglob->gl_pathc == 1 && auto_complete(pglob) == -1)
		return (-1);
	globfree(pglob);
	return (0);
}
