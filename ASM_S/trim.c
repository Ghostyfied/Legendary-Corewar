#include "asm.h"

static int	iswspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	count_len(char *s)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (!iswspace(s[i]))
		{
			len++;
			i++;
		}
		else if (iswspace(s[i]))
		{
			while (iswspace(s[i]))
				i++;
			if (s[i])
				len++;
		}
	}
	return (len);
}

char		*free_strtrim(char *s)
{
	int j;
	int i;
	int len;
	char *trim;

	i = 0;
	if (!s)
		return (NULL);
	while (iswspace(s[i]))
		i++;
	if (!s[i])
		return (NULL);
	len = count_len(&s[i]);
	trim = (char*)ft_memalloc(sizeof(char) * (len + 1));
	j = 0;
	while (s[i] && j < len)
	{
		if (iswspace(s[i]))
		{
			trim[j] = ' ';
			j++;
			while (iswspace(s[i]))
				i++;
		}
		else
		{
			trim[j] = s[i];
			i++;
			j++;
		}
	}
	trim[j] = '\0';
	return (trim);
}
