/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosmeni <akosmeni@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:09:07 by akosmeni          #+#    #+#             */
/*   Updated: 2025/07/22 13:07:33 by akosmeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*arr;
	unsigned char	*p;
	size_t			i;
	size_t			total_size;

	i = 0;
	total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size)
		return (NULL);
	arr = malloc(total_size);
	if (!arr)
		return (NULL);
	p = (unsigned char *)arr;
	while (i < total_size)
	{
		p[i] = 0;
		i++;
	}
	return (arr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*res;
	size_t		len1;
	size_t		len2;

	len1 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[len1] != '\0')
		++len1;
	len2 = 0;
	while (s2[len2] != '\0')
		++len2;
	res = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	return (ft_memcpy(res + len1, s2, len2), res[len1 + len2] = '\0', res);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*temp;
	const char	*source;

	i = 0;
	temp = (char *)dest;
	source = (const char *)src;
	while (i < n)
	{
		temp[i] = source[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*arr;
	int		i;

	i = 0;
	if (!s)
	{
		arr = ft_calloc(1, sizeof(char));
		if (!arr)
			return (NULL);
		return (arr[0] = '\0', arr);
	}
	while (s[i] != '\0')
		i++;
	arr = ft_calloc(i + 1, sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}
