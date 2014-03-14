#include <ft_strings.h>

int		is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		is_sep(char c)
{
	if ((c == '|') || (c == '>') || (c == '<'))
		return (1);
	else
		return (0);
}

int		is_sep_space(char c)
{
	if (is_space(c))
		return (1);
	else if (is_sep(c))
		return (1);
	return (0);
}

