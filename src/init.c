/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:50:34 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:12:15 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int			init_term(char **env)
{
	int		i;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], "TERM=", 5) != 0))
		i++;
	if (!env[i])
		return (ft_error("Error in env --> No TERM set\n"));
	if (tgetent(NULL, env[i] + 5) <= 0)
		return (ft_error("Error tgetent couldn't load the termcap entry\n"));
	return (0);
}

int			store_io(t_shell *shell)
{
	if ((shell->store_io[0] = dup(0)) == -1
		|| (shell->store_io[1] = dup(1)) == -1)
		return (ft_error("Error, couldn't dup the file_descriptors\n"));
	return (0);
}

t_env		*get_root(void)
{
	t_env	*root;

	if ((root = (t_env *)malloc(sizeof(t_env))) == NULL)
		return ((t_env *)ft_error_null("Error, couldn't malloc\n"));
	root->next = root;
	root->prev = root;
	root->var = NULL;
	root->pos = 1;
	root->num = 0;
	return (root);
}

t_env		*put_in_list(t_env *root, char *param)
{
	t_env	*new_env;

	if ((new_env = (t_env *)malloc(sizeof(t_env))) == NULL)
		return ((t_env *)ft_error_null("Error, couldn't malloc\n"));
	new_env->num = root->prev->num + 1;
	new_env->prev = root->prev;
	new_env->next = root;
	root->prev->next = new_env;
	root->prev = new_env;
	if (!(new_env->var = ft_strdup(param)))
		return ((t_env *)ft_error_null("Error, couldn't strdup\n"));
	new_env->pos = -1;
	return (new_env);
}

t_env		*get_env(char **env)
{
	int		i;
	t_env	*root;

	i = 0;
	if ((root = get_root()) == NULL)
		return (NULL);
	while (env[i])
		if (put_in_list(root, env[i++]) == NULL)
			return (NULL);
	return (root);
}
