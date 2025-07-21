/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:09:05 by akosmeni          #+#    #+#             */
/*   Updated: 2025/07/21 18:00:01 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract(char *str)
{
	char	*to_return;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	if (str[i] == '\n')
		to_return = ft_calloc(i + 2, sizeof(char));
	else
		to_return = ft_calloc(i + 1, sizeof(char));
	if (!to_return)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		to_return[i] = str[i];
		++i;
	}
	if (str[i] == '\n')
		to_return[i++] = '\n';
	to_return[i] = '\0';
	return (to_return);
}

char	*join(char **str1, char *str2)
{
	char	*res;

	if (!str2)
		return (NULL);
	if (!*str1)
	{
		*str1 = ft_strdup("");
		if (!*str1)
			return (NULL);
	}
	res = ft_strjoin(*str1, str2);
	if (!res)
		return (free (*str1), res = NULL, NULL);
	free(*str1);
	*str1 = NULL;
	return (res);
}

char	*if_checker(char **rest, char **joiner, int *i)
{
	char	*res;

	if (ft_strchr(*joiner, '\n') && *i > 0)
	{
		res = extract(*joiner);
		if (*rest)
			free (*rest);
		*rest = ft_strdup(ft_strchr(*joiner, '\n') + 1);
		return (free (*joiner), res);
	}
	else if (!ft_strchr(*joiner, '\n') && (*joiner)[0])
	{
		if (!*rest || (*rest)[0] == '\0')
		{
			res = ft_strdup(*joiner);
			if (*rest)
				free (*rest);
			return (free(*joiner), *rest = NULL, res);
		}
		res = ft_strdup(*rest);
		free (*rest);
		return (free (*joiner), *rest = NULL, res);
	}
	return (free (*joiner), free (*rest), *rest = NULL, NULL);
}

char	*checker(char *buffer, char **rest, int fd)
{
	char	*result;
	char	*joiner;
	int		i;

	if (*rest && (*rest)[0] != '\0')
		joiner = ft_strdup(*rest);
	else
		joiner = ft_strdup("");
	if (!joiner)
	{
		if (*rest && (*rest)[0] != '\0')
			return (free(*rest), NULL);
		else
			return (NULL);
	}
	i = 1;
	while (!ft_strchr(joiner, '\n') && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (free(joiner), NULL);
		buffer[i] = '\0';
		joiner = join(&joiner, buffer);
	}
	return (result = if_checker(rest, &joiner, &i), result);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	res = checker(buffer, &rest, fd);
	free (buffer);
	return (res);
}
