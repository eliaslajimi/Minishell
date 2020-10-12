#include "libft.h"

int		ft_strrcmp(const char *s1, const char *s2)
{
	int	i;
	int	j;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	j = 0;
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	i -= 1;
	j -= 1;
	while (i >= 0 && j >= 0 && str1[i] == str2[j])
	{
		i--;
		j--;
	}
	return (str1[i] - str2[j]);
}
