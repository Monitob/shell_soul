#include <mnsh.h>

static int	set_env_check(void);
static int	set_env_overwrite(char *name);
static char	*set_env_new(char *name, char *value);
static void	set_env_final(char *new_env_str);

void		set_env(void)
{
	char	*new_env_str;
	char	*name;
	char	*value;

	name = g_cmd[0].my_argv[1];
	value = g_cmd[0].my_argv[2];
	if (set_env_check() == 0)
		return ;
	if ((set_env_overwrite(name)) < 0)
		return ;
	if ((new_env_str = set_env_new(name, value)) == NULL)
		return ;
	set_env_final(new_env_str);
}

static void	set_env_final(char *new_env_str)
{
	char	**new_env;
	char	**env;
	int		i;

	env = environ;
	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*env)
	{
		new_env[i++] = ft_strdup(*env);
		env++;
	}
	new_env[i++] = ft_strdup(new_env_str);
	new_env[i] = NULL;
	environ = new_env;
}

static char	*set_env_new(char *name, char *value)
{
	char	*new_env_str;

	new_env_str = (char *)malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (new_env_str == NULL)
	{
		ft_putstr_fd("\x1b[31mERROR\x1b[0m --> \n", 2);
		ft_putstr_fd("Not engouh memory to store new env variable\n", 2);
		return (NULL);
	}
	ft_strcpy(new_env_str, name);
	ft_strcat(new_env_str, "=");
	ft_strcat(new_env_str, value);
	return (new_env_str);
}

static int	set_env_overwrite(char *name)
{
	int	over;

	over = 0;
	over = ft_atoi(g_cmd[0].my_argv[3]);
	if (over == 0 && get_env_var(name) != NULL)
		return (-1);
	unset_env();
	return (over);
}

static int	set_env_check(void)
{
	char	*name;
	char	*value;

	name = g_cmd[0].my_argv[1];
	value = g_cmd[0].my_argv[2];
	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL
			|| value == NULL || g_cmd[0].my_argv[3] == NULL)
	{
		ft_putstr_fd("[\x1b[31msetenv\x1b[0m] --> ", 2);
		ft_putstr_fd("\x1b[33mIncorrect arguments\x1b[0m\n", 2);
		ft_putstr_fd("[\x1b[36mUsage\x1b[0m]  --> ", 2);
		ft_putstr_fd("setenv [name] [value] [overwrite? 0=yes 1=no]\n", 2);
		return (0);
	}
	return (1);
}
