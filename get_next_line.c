/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misi-moh <misi-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:43:58 by misi-moh          #+#    #+#             */
/*   Updated: 2023/01/22 18:08:18 by misi-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		line[BUFFER_SIZE + 1];
	char			*next_line;
	int				i;

	if (BUFFER_SIZE < 1 || fd == -1 || FOPEN_MAX < fd)
		return (0);
	next_line = ft_strjoin(0, line);
	if (ft_cleanit(line) > 0)
		return (next_line);
	i = read(fd, line, BUFFER_SIZE);
	if (i < 0)
	{
		free(next_line);
		return (NULL);
	}
	while (i > 0)
	{
		next_line = ft_strjoin(next_line, line);
		if (ft_cleanit(line) > 0)
			break ;
		i = read(fd, line, BUFFER_SIZE);
	}
	return (next_line);
}

/*
 int	main(void)
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