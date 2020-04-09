#include "libft.h"

void ft_putstr(char *str)
{
    int len;

    len = ft_strlen(str);
    write(1, str, len);
    return ;
}