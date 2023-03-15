/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:18:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/15 00:29:52 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*store_extra_char(char	*buffer)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free (buffer);
		return (NULL);
	}
	temp = (char *) malloc (sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!temp)
		return (NULL);
	j = 0;
	i++;
	while (buffer[i] != '\0')
	{
		temp[j++] = buffer[i++];
	}
	temp[j] = '\0';
	free (buffer);
	return (temp);
}

char	*get_line(char	*buffer)
{
	int		i;
	char	*dst;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	dst = (char *) malloc (sizeof(char) * (i + 2));
	if (!dst)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		dst[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		dst[i] = '\n';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*read_and_join(int fd, char	*dst, int buffer_size)
{
	int		char_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * (buffer_size + 1));
	if (!buffer)
		return (NULL);
	char_read = 1;
	while (!ft_strchr(dst, '\n') && char_read != 0)
	{
		char_read = read(fd, buffer, buffer_size);
		if (char_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[char_read] = '\0';
		dst = ft_strjoin(dst, buffer);
	}
	free (buffer);
	return (dst);
}

char	*get_next_line(int fd, int buffer_size)
{
	char		*current_line;
	static char	*buffer;

	if (fd < 0 || buffer_size <= 0)
		return (NULL);
	buffer = read_and_join(fd, buffer, buffer_size);
	if (!buffer)
		return (NULL);
	current_line = get_line(buffer);
	// if (!current_line)
	// 	return (NULL);
	buffer = store_extra_char(buffer);
	return (current_line);
}