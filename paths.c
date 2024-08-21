#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static size_t ft_tlen(size_t len_s, unsigned int start, size_t len)
{
	size_t i;

	i = ft_min(len_s, len);
	if (start + len > len_s)
		i = len_s - start;
	return (i + 1);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *res;
	size_t slen;
	size_t i;

	if (!s)
		return (NULL);
	slen = strlen(s);
	if (start > slen)
	{
		start = 0;
		len = 0;
	}
	res = (char *)malloc(sizeof(char) * ft_tlen(slen, start, len));
	if (!res)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
static int ft_countwords(char const *str, char delim)
{
	int i;
	int res;

	if (!str || !str[0])
		return (0);
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == delim && i > 0)
		{
			if (str[i - 1] != delim)
				res++;
		}
		i++;
	}
	if (str[i] == '\0' && str[i - 1] != delim)
		res++;
	return (res);
}

char **ft_split(char const *s, char c)
{
	char **res;
	int i;
	int h;
	int v;

	res = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!res || !s)
		return (NULL);
	i = -1;
	h = 0;
	v = 0;
	while (s[++i])
	{
		if (v > 0 && s[i] == c)
		{
			res[h++] = ft_substr(s, i - v, v);
			v = 0;
		}
		else if (s[i] != c)
			v++;
	}
	if (v > 0)
		res[h++] = ft_substr(s, i - v, v);
	res[h] = 0;
	return (res);
}

char *join_path(char const *s1, char const *s2)
{
	char *ret;
	size_t s1_len;
	size_t s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = strlen(s1);
	s1_len -= s1[s1_len - 1] == '/';
	s2_len = strlen(s2);
	s2_len -= s2[s2_len - 1] == '/';
	ret = malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (ret == NULL)
		return (NULL);
	memcpy(ret, s1, s1_len);
	memcpy((ret + s1_len + 1), s2, s2_len);
	ret[s1_len] = '/';
	ret[s1_len + s2_len + 1] = '\0';
	return (ret);
}

char *diminish_path(char *path)
{
	char *ret;
	int i;
	int j;
	int k;
	char **elems;

	elems = ft_split(path, '/');
	i = 0;
	j = 0;
	while (elems[i])
	{
		if (strcmp(elems[i], "..") == 0)
		{
			j -= j > 0;
		}
		else if (strcmp(elems[i], "."))
		{
			elems[j] = elems[i];
			j++;
		}
		i++;
	}
	elems[j] = '\0';
	if (j == 0)
		return strdup("/");
	j = 0;
	i = 0;
	while (elems[i])
	{
		j += strlen(elems[i]);
		i++;
	}
	ret = malloc(j + i + 2);
	k = 0;
	i = 0;
	while (elems[i])
	{
		j = 0;
		ret[k] = '/';
		k++;
		while (elems[i][j])
		{
			ret[k] = elems[i][j];
			j++;
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	i = 0;
	return ret;
}

char *resolve_path(char *pwd, char *path)
{
	char *ret;
	char *temp;

	ret = NULL;
	if (path == NULL || pwd == NULL)
		return (pwd);
	if (path[0] == '/')
		temp = strdup(path);
	else
		temp = join_path(pwd, path);
	if (temp == NULL)
		return (pwd);
	ret = diminish_path(temp);
	return ret;
}

int main(int argc, char **argv)
{
	(void)argc;
	char *res = resolve_path(argv[1], argv[2]);
	printf("%s + %s = %s\n", argv[1], argv[2], res);
}
