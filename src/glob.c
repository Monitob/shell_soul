/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:42:49 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:15:45 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_cmd		*globing(t_cmd *tmp)
{
	glob_t			gb;
	int				flags;
	unsigned int	i;
	char			*word;
	t_cmd			*new_elem;

	flags = GLOB_NOMAGIC;
	i = 0;
	if ((glob(tmp->word, flags, NULL, &gb)) != 0)
	{
		ft_putstr("No match for ");
		ft_putstr(tmp->word);
		ft_putchar('\n');
	}
	if (gb.gl_pathc == 0)
		return (tmp->next);
	while (i < gb.gl_pathc)
	{
		if ((word = ft_strdup(gb.gl_pathv[i++])) == NULL)
			return (ft_error_null("Couldn't strdup\n"));
		new_elem = add_to_list(tmp, word);
	}
	del_node(tmp);
	globfree(&gb);
	return (new_elem->next);
}

void		globing_for_cd_manage(glob_t gb, t_cmd *cmd)
{
	if (gb.gl_pathc == 0)
	{
		ft_putstr("No match for ");
		ft_putstr(cmd->word);
		ft_putchar('\n');
	}
	else if (gb.gl_pathc > 1)
	{
		ft_putstr("Ambiguous input : ");
		ft_putstr(cmd->word);
		ft_putchar('\n');
	}
}

char		*globing_for_cd(t_cmd *cmd)
{
	glob_t	gb;
	int		flags;

	flags = GLOB_NOMAGIC | GLOB_TILDE;
	cmd = cmd->next;
	if ((glob(cmd->word, flags, NULL, &gb)) != 0)
	{
		ft_putstr("No match for ");
		ft_putstr(cmd->word);
		ft_putchar('\n');
		return (NULL);
	}
	if ((int)gb.gl_pathc >= 0)
		globing_for_cd_manage(gb, cmd);
	else
		return (ft_strdup(gb.gl_pathv[0]));
	globfree(&gb);
	return (NULL);
}

int			globing_for_echo(t_cmd *cmd)
{
	glob_t			gb;
	int				flags;
	unsigned int	i;

	flags = GLOB_NOMAGIC;
	i = 0;
	if ((glob(cmd->word, flags, NULL, &gb)) != 0)
	{
		ft_putstr("No match for ");
		ft_putstr(cmd->word);
		ft_putchar('\n');
	}
	while (i < gb.gl_pathc)
	{
		ft_putstr(gb.gl_pathv[i++]);
		ft_putchar(' ');
	}
	globfree(&gb);
	return (0);
}

char		*globing_for_setenv(t_cmd *cmd)
{
	glob_t			gb;
	int				flags;
	char			*value;
	unsigned int	i;

	flags = GLOB_NOMAGIC;
	if ((glob(cmd->next->word, flags, NULL, &gb)) != 0)
	{
		ft_putstr("No match for ");
		ft_putstr(cmd->word);
		ft_putchar('\n');
		return ("");
	}
	i = 0;
	value = NULL;
	while (i < gb.gl_pathc)
	{
		if ((value = ft_strcat(value, gb.gl_pathv[i++])) == NULL)
			return (NULL);
		if (i < gb.gl_pathc)
			if ((value = ft_strcat(value, " ")) == NULL)
				return (NULL);
	}
	globfree(&gb);
	return (value);
}
