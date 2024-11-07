#include "stdlib.h"

char	*ft_strndup(char *src, int n)
{
	char	*dup_str;
	int		i;

	if (src == NULL || n < 0)
		return (NULL);
	dup_str = malloc(sizeof(char) * n);
	if (dup_str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup_str[i] = src[i];
		++i;
	}
	return (dup_str);
}

char	*ft_strjoin(char *s1, char *s2, int len2)
{
	char	*joined_str;
	int		len1;

	len1 = 0;
	while (s1[len1])
		++len1;
	joined_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (joined_str)
	{
		joined_str[len1 + len2] = '\0';
		while (len2)
		{
			joined_str[len1 + len2 - 1] = s2[len2 - 1];
			--len2;
		}
		while (len1)
		{
			joined_str[len1 - 1] = s1[len1 - 1];
			--len1;
		}
	}
	free(s1);
	return (joined_str);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	if (c == '\0')
		return (i);
	return (-1);
}
