
#include "cub3d.h"



int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char )s1[i] - (unsigned char)s2[i]);
	i++;
	}	
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;
	int		i;

	len = ft_strlen(s1);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);

	while (*haystack && needle_len <= len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	int		digit_count;

	digit_count = 0;
	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && result <= 2147483649)
	{
		result = (result * 10) + str[i++] - '0';
		digit_count++;
	}
	if (str[i] != '\0' || digit_count == 0)
	{
		return (2147483649);
	}
	return (sign * result);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*s;

	if (dst == src)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (unsigned char *)dst;
	i = 0;
	s = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	return (dst);
}
