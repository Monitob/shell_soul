#include <stdlib.h>
#include <ft_strings.h>
#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	return (NULL);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	char	*ptr;
	int		len_s1;

	len_s1 = ft_strlen(s1);
	if(!(str = (char *)malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1))))
		return (NULL);
	ptr = str;
	ft_strncpy(str, s1, len_s1);
	str += len_s1;
	ft_strcpy(str, s2);
	return (ptr);
}

char	*ft_strcat(char *s1, const char *s2)
{
	char	*ptr;

	ptr = s1;
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr)
		ptr++;
	return (ptr - s);
}


char	*ft_strcpy(char *s1, const char *s2)
{
	char	*ptr;

	ptr = s1;
	while (*s2)
	{
		*s1++ = *s2++;
	}
	*s1 = '\0';
	return (ptr);
}

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	char	*ptr;

	ptr = s1;
	while (*s2 && n-- > 0)
		*s1++ = *s2++;
	while (n-- > 0)
		*s1++ = '\0';
	return (ptr);
}

void	ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putstr_fd(const char *s,int fd)
{
	write(fd, s, ft_strlen(s));
}
void	ft_putendl(const char *s)
{
	ft_putstr(s);
	ft_putstr("\n");
}

char	*ft_strdup(const char *s1)
{
	const char	*ptr;
	char		*ptr2;
	char		*cpy;

	ptr = s1;
	while (*ptr)
		ptr++;
	if (!(cpy = (char *)malloc(sizeof(char) * (ptr - s1 + 1))))
		return (NULL);
	ptr2 = cpy;
	while (*s1)
		*cpy++ = *s1++;
	*cpy = '\0';
	return (ptr2);
}
