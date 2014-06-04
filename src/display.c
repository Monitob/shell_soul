/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:44:49 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 18:46:54 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int		display_cur_dir(void)
{
	int		ret;
	glob_t	pglob;

	if ((ret = glob("*", GLOB_NOMAGIC | GLOB_TILDE, NULL, &pglob))
		&& ret != GLOB_NOMATCH)
		return (ft_error("fail glob"));
	ft_putchar('\n');
	if (pglob.gl_pathc == 0)
		return (0);
	if (display_glob(&pglob) == -1)
		return (-1);
	return (0);
}

int		display_bin(char *word, t_shell *shell)
{
	int			i;
	int			ret;
	glob_t		pglob;
	char		*pattern;

	i = 0;
	if ((pattern = ft_strcat(word, "*")) == NULL
		|| ((ret = glob(pattern, GLOB_NOMAGIC | GLOB_TILDE, NULL, &pglob))
		&& ret != GLOB_NOMATCH))
		return (ft_error("fail glob"));
	ft_putchar('\n');
	while (shell->path && shell->path[i])
	{
		free(pattern);
		if ((pattern = ft_strcat(shell->path[i], word)) == NULL
			|| (pattern = ft_strcat(pattern, "*")) == NULL
			|| ((ret = glob(pattern, GLOB_NOMAGIC | GLOB_TILDE | GLOB_APPEND,
			NULL, &pglob)) && ret != GLOB_NOMATCH))
			return (ft_error("fail glob"));
		++i;
	}
	if (pglob.gl_pathc && display_glob(&pglob) == -1)
		return (-1);
	free(pattern);
	return (0);
}

int		display_path(char *word)
{
	int			ret;
	glob_t		pglob;
	char		*pattern;

	if ((pattern = ft_strcat(word, "*")) == NULL
		|| ((ret = glob(pattern, GLOB_NOMAGIC | GLOB_TILDE, NULL, &pglob))
		&& ret != GLOB_NOMATCH))
		return (ft_error("fail glob"));
	ft_putchar('\n');
	if (pglob.gl_pathc == 0)
		return (0);
	if (display_glob(&pglob) == -1)
		return (-1);
	free(pattern);
	return (0);
}
