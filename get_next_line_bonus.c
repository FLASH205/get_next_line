/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:57:14 by ybahmaz           #+#    #+#             */
/*   Updated: 2024/12/20 09:37:56 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_new_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (free(line), line = NULL, NULL);
	str = malloc(ft_strlen(line) - i + 1);
	if (!str)
		return (free(line), line = NULL, NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	return (free(line), line = NULL, str);
}

char	*read_line(int fd, char *line)
{
	char	*buff;
	int		n_bytes;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(line), line = NULL, NULL);
	n_bytes = 1;
	while (!ft_strchr(line) && n_bytes != 0)
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		if (n_bytes < 0)
			return (free(buff), buff = NULL, NULL);
		buff[n_bytes] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			return (free(buff), buff = NULL, NULL);
	}
	return (free(buff), buff = NULL, line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd < OPEN_MAX)
		{
			free(line[fd]);
			line[fd] = NULL;
		}
		return (NULL);
	}
	line[fd] = read_line(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	str = extract_line(line[fd]);
	if (!str)
		return (free(line[fd]), line[fd] = NULL, NULL);
	line[fd] = ft_new_line(line[fd]);
	if (!line[fd])
		return (str);
	return (str);
}
