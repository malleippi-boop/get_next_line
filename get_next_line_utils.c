/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmanett <frmanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:53:14 by frmanett          #+#    #+#             */
/*   Updated: 2026/01/12 18:29:34 by frmanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *) s);
		if (*s == '\0')
			break ;
		s++;
	}
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
	
	if (!s1 || !s2)
		return (NULL);
	lens1 = (ft_strlen (s1));
	lens2 = (ft_strlen (s2));
	join = malloc(lens1 + lens2 + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (++i < lens1)
		join[i] = s1[i];
	j = 0;
	while (j < lens2)
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}