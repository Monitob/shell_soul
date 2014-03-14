#include <ft_strings.h>

static int	ft_istreated(char c);

int			ft_atoi(const char *str)
{
    int         n;
    int         ndigit;
    const char  *ptr;

    if (!(*str) || (!ft_istreated(*str) && !ft_isdigit(*str))
        || ((*str == '+' || *str == '-') && !ft_isdigit(*(str + 1))))
        return (0);
    if (*str == '+' || *str == '-')
        str++;
    while (ft_istreated(*str))
        str++;
    ptr = str;
    ndigit = 10;
    while (ft_isdigit(*str))
        str++;
    n = *(--str) - '0';
    --str;
    while (str >= ptr)
    {
        n += (*(str--) - '0') * ndigit;
        ndigit *= 10;
    }
    if (*(ptr - 1) == '-')
        n *= -1;
    return (n);
}

int			ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int	ft_istreated(char c)
{
    if (c == '+' || c == '-' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
        || c == '\r' || c == ' ')
        return (1);
    return (0);
}
