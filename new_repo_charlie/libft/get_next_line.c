/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:48:32 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/02/05 13:51:09 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_strchr_gnl(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str++ == '\n')
			return (1);
	}
	return (0);
}

static char			*ft_cut_ifeol(char *s1)
{
	int				i;
	int				end;
	char			*result;

	i = 0;
	end = 0;
	if (!s1)
		return (NULL);
	while (s1[end] && s1[end] != '\n')
		end++;
	if (!(result = malloc(sizeof(char) * (end + 1))))
		return (NULL);
	while (i < end)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char			*ft_strjoin_gnl(char *s1, char *s2)
{
	int				len1;
	int				len2;
	char			*str;

	if (!s1)
		return (ft_cut_ifeol(s2));
	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2] && s2[len2] != '\n')
		len2++;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	ft_strdel(&s1);
	return (str);
}

static char			*to_next(int fd, char **tab, char *buf, int ret)
{
	int				i;
	int				j;
	char			*str;

	i = 0;
	j = 0;
	while (i <= ret && buf[i] != '\n')
		i++;
	i++;
	if (ret == 0)
		ret = i;
	if (!(str = malloc(sizeof(char) * (ret - i + 1))))
		return (NULL);
	while (i + j < ret)
	{
		str[j] = buf[i + j];
		j++;
	}
	str[j] = 0;
	ft_strdel(&tab[fd]);
	return (str);
}

static int			end_or_error(int fd, int ret, char **buf, char **tab)
{
	if (ret != 1)
		if (fd >= 0 && fd <= OPEN_MAX)
			ft_strdel(&(*tab));
	if (buf)
		ft_strdel(&(*buf));
	return ((ret == 0) ? 0 : -1);
}

static int			gnl(int fd, char **tab, char **line)
{
	int				ret;
	int				newline;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(*line = ft_cut_ifeol("")))
		return (-1);
	if (!tab[fd])
		return (0);
	ret = 0;
	ft_strdel(&(*line));
	if (!(*line = ft_cut_ifeol(tab[fd])))
		return (-1);
	while (tab[fd][ret])
		ret++;
	if ((newline = ft_strchr_gnl(tab[fd])) != 0)
	{
		if (!(tab[fd] = to_next(fd, tab, tab[fd], ret)))
			return (-1);
		return ((*line == NULL || newline == 0) ? 0 : 1);
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	int				ret;
	int				to_ret;
	char			*buf;
	static char		*tab[OPEN_MAX];

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (end_or_error(fd, -1, &buf, &(tab[fd])));
	if ((to_ret = gnl(fd, tab, line)) == 0)
	{
		while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[ret] = 0;
			if (!(*line = ft_strjoin_gnl(*line, buf)))
				return (end_or_error(fd, -1, &buf, &(tab[fd])));
			if ((ft_strchr_gnl(buf)))
				break ;
		}
		if (!(tab[fd] = to_next(fd, tab, buf, ret)))
			return (end_or_error(fd, -1, &buf, &(tab[fd])));
		to_ret = (!(ret) ? 0 : 1);
	}
	end_or_error(fd, to_ret, &buf, &(tab[fd]));
	return (to_ret);
}

/*
 ** int main(int argc, char **argv)
 **{
 **	int i = 1;
 **	int fd;
 **	int ret;
 **	char *line;
 **
 **	while (i < argc)
 **	{
 **		fd = open(argv[i], O_RDONLY);
 **		while ((ret = get_next_line(fd, &line))> 0)
 **		{
 **			printf("%d [%s]\n",ret, line);
 **			free(line);
 **			line = NULL;
 **		}
 **		printf("%d [%s]\n", ret, line);
 **		free(line);
 **		line = NULL;
 **		close(fd);
 **		i++;
 **	}
 **	system("leaks a.out");
 **
 **	return(0);
 **}
 */
