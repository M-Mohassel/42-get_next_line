/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misi-moh <misi-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:43:58 by misi-moh          #+#    #+#             */
/*   Updated: 2023/01/18 15:00:02 by misi-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	readts(char *buff, int fd, char **str)
{
	char	*tmp;
	int		i;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		i = read(fd, buff, BUFFER_SIZE);
		while (i > 0)
		{
			buff[i] = 0;
			if (!*str)
				*str = ft_substr(buff, 0, i);
			else
			{
				tmp = *str;
				*str = ft_strjoin(*str, buff);
				free(tmp);
			}
			if (ft_strchr(*str, '\n'))
				break ;
			i = read(fd, buff, BUFFER_SIZE);
		}
	}
	free(buff);
}

static char	*fts(char **str)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	if (!*str || *str[0] == '\0')
	{
		free(*str);
		return (0);
	}
	if (!ft_strchr(*str, '\n'))
	{
		ret = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = 0;
		return (ret);
	}
	i = ft_strlen(*str);
	j = ft_strlen(ft_strchr(*str, '\n'));
	ret = ft_substr(*str, 0, i - j + 1);
	tmp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, j - 1);
	free(tmp);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buffer, 0) == -1)
	{
		free(buffer);
		return (0);
	}
	readts(buffer, fd, &str);
	return (fts(&str));
}

/*int	main(void)
{
	int fd;
	
	fd = open("only_nl.txt", O_RDONLY);
	
	char *ptr = get_next_line(fd);
	printf(" LINE 1 : %s\n",ptr);
	free(ptr);

	ptr = get_next_line(fd);
	printf(" LINE 2 : %s\n",ptr);
	free(ptr);
	
	ptr = get_next_line(fd);
	printf(" LINE 3 : %s\n",ptr);
	free(ptr);

	ptr = get_next_line(fd);
	printf(" LINE 4 : %s\n",ptr);
	free(ptr);

	ptr = get_next_line(fd);
	printf(" LINE 4 : %s\n",ptr);
	free(ptr);

	ptr = get_next_line(fd);
	printf(" LINE 5 : %s\n",ptr);
	free(ptr);
	
	close(fd);
}
*/
