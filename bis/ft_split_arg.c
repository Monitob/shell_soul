#include <mnsh.h>

static int	len_str(const char *str);
static int	nb_args(const char *str);

char	**ft_split_arg(char *str)
{
	char	**arr;
	int		nb;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	nb = nb_args(str);
	if (!(arr = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (!(arr[i] = (char *)malloc(sizeof(char) * (len_str(str) + 1))))
			return (NULL);
		j = 0;
		while (*str != '\0' && !is_sep_space(*str))
			arr[i][j++] = *str++;
		arr[i][j] = '\0';
		while (*str != '\0' && !is_sep(*str) && is_space(*str))
			str++;
		i++;
	}
	arr[i] = NULL;
	return (arr);

}

static int	nb_args(const char *str)
{
	int	nb;

	while (*str == ' ')
		str++;
	if (*str == '\0' || is_sep(*str))
		return (0);
	nb = 1;
	while (*str && !is_sep(*str))
	{
		if (is_space(*str) && !is_sep_space(*(str + 1))
			&& (*(str + 1) != '\0'))
			++nb;
		++str;
	}
	return (nb);
}

static int	len_str(const char *str)
{
	int	len;

	len = 0;
	while (*str != '\0' && !is_sep_space(*str))
	{
		len++;
		str++;
	}
	return (len);
}
