#include "header.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return ((size_t) i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	joined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (joined == NULL)
	{
		free((char *)s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	free((char *)s1);
	return (joined);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*des;
	unsigned char	*sr;

	des = dest;
	sr = (unsigned char *)src;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (des < sr)
	{
		while (n--)
			*des++ = *sr++;
	}
	else
	{
		des += n;
		sr += n;
		while (n--)
		{
			des--;
			sr--;
			*des = *sr;
		}
	}
	return (dest);
}
