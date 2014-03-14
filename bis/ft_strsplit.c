#include <ft_strings.h>

static int	len_str(const char *str, char c);

char		**ft_strsplit(const char *str, char c)
{
	char	**arr;
	int		nb;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	while (*str == c)
		str++;
	nb = nb_split(str, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (!(arr[i] = (char *)malloc(sizeof(char) * (len_str(str, c) + 1))))
			return (NULL);
		j = 0;
		while (*str != '\0' && *str != c)
			arr[i][j++] = *str++;
		arr[i][j] = '\0';
		while (*str != '\0' && *str == c)
			str++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int			nb_split(const char *str, char c)
{
	int	nb;

	while (*str == c)
		str++;
	if (*str == '\0')
		return (0);
	nb = 1;
	while (*str)
	{
		if (*str == c && *(str + 1) != c && *(str + 1) != '\0')
			++nb;
		++str;
	}
	return (nb);
}

static int	len_str(const char *str, char c)
{
	int	len;

	len = 0;
	while (*str != '\0' && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}
