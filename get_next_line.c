/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:09:05 by akosmeni          #+#    #+#             */
/*   Updated: 2025/07/16 14:14:11 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*extract(char *str)
{
	char *to_return;
	size_t i;

	i = 0;
	while(str[i] && str[i] != '\n')
		++i;
	if (str[i] == '\n')
		to_return = calloc(i + 2, sizeof(char));
	else 
		to_return = calloc(i + 1, sizeof(char));
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

char *join(char *str1, char *str2)
{
	char *res;
	
	if(!str1)
		str1 = ft_strdup("");
	if (!str1 || !str2)
		return (NULL);
	res = ft_strjoin(str1, str2);
	free(str1);
	return (res);
}

char	*checker(char *buffer, char **rest, int fd)
{
	char	*result;
	char	*joiner;
	int		i;

	if (*rest)
		joiner = ft_strdup(*rest);
	else
		joiner = ft_strdup("");
	while (!ft_strchr(joiner, '\n') && (i = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[i] = '\0';
		printf("To join rest: \"%s\" and buffer: \"%s\"\n", *rest, buffer);
		joiner = join(joiner, buffer);
		free(*rest);
		*rest = ft_strdup(joiner);
		printf("After join: \"%s\"\n", joiner);
		printf("i = %d\n", i);
		printf("Rest = \"%s\"\n\n", *rest);
	}
	if(i < 0)
		return (free(joiner), NULL);
	if (ft_strchr(joiner, '\n') && i > 0)
	{
		result = extract(joiner);
		printf("Line with '\\n' sign: \"%s\"\n", result);
		//free(*rest);
		*rest = ft_strdup(ft_strchr(joiner, '\n') + 1);
		printf("Everything after '\\n': \"%s\"\n", *rest);
		free (joiner);
		return (result);
	}
	else if(!ft_strchr(joiner, '\n') && i == 0 && joiner && *joiner)
	{
		result = ft_strdup(*rest);
		free (joiner);
		*rest = NULL;
		return (result);			
	}
	free(joiner);
	*rest = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *rest;
	char *buffer;
	char *res;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE+1, sizeof(char));
	if(!buffer)
		return (NULL);
	res = checker(buffer, &rest, fd);
	free (buffer);
	return (res);
}
