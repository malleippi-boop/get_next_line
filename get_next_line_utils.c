/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmanett <frmanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:53:14 by frmanett          #+#    #+#             */
/*   Updated: 2026/01/19 18:54:21 by frmanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	char	*join;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2)); // al primo ciclo faccio lo strdup del mio buffer che poi diventera' la mia statica
	if (!s2)
		return (NULL);
	lens1 = (ft_strlen (s1));
	lens2 = (ft_strlen (s2));
	join = malloc(lens1 + lens2 + 1);
	if (!join)
		return (NULL);
	i = -1; // per norminette, facendo ++i dopo arriva subito a 0 e parte da li
	while (++i < lens1)
		join[i] = s1[i];
	j = 0;
	while (j < lens2)
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*duplicate;

	i = 0;
	if (!s)
		return (NULL);
	duplicate = (char *) malloc(ft_strlen(s) + 1);
	if (!duplicate)
	{
		return (NULL);
	}
	while (s[i])
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
