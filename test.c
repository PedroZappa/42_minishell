#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib/libft/libft/libft.h"

int	ft_check_alpha(char c)
{
	if (isalpha(c) || c == '_')
		return (0);
	return (1);
}

int	ft_check_alnum(char c)
{
	if (isalnum(c) || c == '_')
		return (0);
	return (1);
}

char	*ft_fill_var()
{
	return "/home/gfragoso";
}



int main(void)
{
	char *a = "\"yo $USER\"";
	printf("%s\n", a);
	char *ret = ft_expand(a);
	printf("ret -> %s\n", ret);
}