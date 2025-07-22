/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:09:05 by akosmeni          #+#    #+#             */
/*   Updated: 2025/07/22 17:28:58 by akosmeni         ###   ########.fr       */
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
		return (free (*rest), free (*joiner), *rest = NULL, res);
	}
	free (*joiner);
	free (*rest);
	return (*rest = NULL, NULL);
}

char	*checker(char *buffer, char **rest, int fd)
{
	t_checker	chk;

	if (*rest && (*rest)[0] != '\0')
		chk.joiner = ft_strdup(*rest);
	else
		chk.joiner = ft_strdup("");
	if (!chk.joiner)
	{
		if (*rest && (*rest)[0] != '\0')
			return (free(*rest), NULL);
		else
			return (NULL);
	}
	chk.i = 1;
	while (!ft_strchr(chk.joiner, '\n') && chk.i > 0)
	{
		chk.i = read(fd, buffer, BUFFER_SIZE);
		if (chk.i < 0)
			return (free(chk.joiner), NULL);
		buffer[chk.i] = '\0';
		chk.joiner = join(&chk.joiner, buffer);
		if (!chk.joiner)
			return (NULL);
	}
	return (chk.result = if_checker(rest, &chk.joiner, &chk.i), chk.result);
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
