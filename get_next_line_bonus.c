/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:49:48 by gcapa-pe          #+#    #+#             */
/*   Updated: 2023/05/12 13:03:28 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_dick(char *content)
{
	int		i;
	char	*line;

	i = 0;
	if (!ft_strlen(content))
	{
		if (content)
			free(content);
		return (NULL);
	}
	while (content[i] != '\n' && content[i] != '\0')
	{
		i++;
	}
	if (content[i] == '\0')
		i--;
	line = ft_substr(content, 0, i + 1, 0);
	return (line);
}

char	*r_file(int fd, char *content)
{
	char	*tmp;
	int		line_s;

	tmp = (char *)malloc(1 + BUFFER_SIZE * sizeof(char));
	if (!tmp)
		return (NULL);
	line_s = 1;
	while (!ft_strchr(content, '\n') && line_s)
	{
		line_s = read(fd, tmp, BUFFER_SIZE);
		if (line_s < 0)
		{
			free(tmp);
			free(content);
			return (NULL);
		}
		tmp[line_s] = '\0';
		content = ft_strjoin(content, tmp);
	}
	free(tmp);
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*content[1000];
	char		*line;
	int			line_len;
	int			content_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1000)
	{
		return (NULL);
	}
	content[fd] = r_file(fd, content[fd]);
	line = get_dick(content[fd]);
	if (!line)
	{
		content[fd] = NULL;
		return (NULL);
	}
	line_len = ft_strlen(line);
	content_len = ft_strlen(content[fd]);
	content[fd] = ft_substr(content[fd], line_len, content_len - line_len, 1);
	return (line);
}
