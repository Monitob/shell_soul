#include <mnsh.h>

static char	*unset_env_check(char *name);

void	unset_env(void)
{
	char	**env;
	char	**tmp;
	char	*name;
	size_t	len;

	env = environ;
	if ((name = unset_env_check(g_cmd[0].my_argv[1])) == NULL)
		return ;
	len = ft_strlen(name);
	while (*env)
	{
		if ((ft_strncmp(*env, name, len) == 0) && ((*env)[len] == '='))
		{
			tmp = env;
			while (*tmp)
			{
				*tmp = *(tmp + 1);
				tmp++;
			}
		}
		else
			env++;
	}
}

static char	*unset_env_check(char *name)
{
	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
	{
		ft_putstr_fd("[\x1b[31munsetenv\x1b[0m] --> ", 2);
		ft_putstr_fd("\x1b[33mIncorrect arguments\x1b[0m\n", 2);
		ft_putstr_fd("[\x1b[36mUsage\x1b[0m]    --> ", 2);
		ft_putstr_fd("unsetenv [name]\n", 2);
		return (NULL);
	}
	else
		return (name);
}

char	*get_env_var(char *var)
{
	char	**env;

	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, var, ft_strlen(var)) == 0)
			return (*env + ft_strlen(var) + 1);
		env++;
	}
	return (NULL);
}

void	get_env(void)
{
	char	**env;

	env = environ;
	while (*env)
	{
		ft_putendl(*env);
		env++;
	}
}

