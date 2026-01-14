/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmanett <frmanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:52:49 by frmanett          #+#    #+#             */
/*   Updated: 2026/01/14 16:38:58 by frmanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*set_static(char *str, int i)
{
	char	*sstr;
	int		j;

	j = 0;
	while (str[i] != '\n')
		i++;
	while (str[i])
	{
		j++;
		i++;
	}
	sstr = (char *)malloc((j + 1) * sizeof(char));
	if (!sstr)
		return (NULL);
	sstr[j] = '\0';
	j--;
	while (j >= 0)
	{
		sstr[j] = str[i];
		j--;
		i--;
	}
	free (str);
	return (sstr);
}

static char	*copy_line(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	ret = (char *)malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[i] = '\0';
	i--;
	while (i >= 0)
	{
		ret[i] = str[i];
		i--;
	}
	return (ret);
}

static char	*helper(ssize_t check, char *buf, char *str)
{
	char	*temp;

	buf[check] = '\0';
	temp = ft_strjoin(str, buf, -1, 0);
	free (str);
	free (buf);
	return (temp);
}

char	*to_return(char **str)
{
	char	*temp;

	if (*str && ft_strchr(*str, '\n'))
	{
		temp = copy_line(*str);
		*str = set_static(*str, 0);
		return (temp);
	}
	else if (*str)
	{
		temp = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (temp);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buf;
	ssize_t		check;
	static char	*str = NULL;

	if (fd < 0)
		return (NULL);
	check = 1;
	while (check && !ft_strchr(str, '\n'))
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
			return (free (buf), NULL);
		if (check == 0 && !str)
		{
			free (buf);
			break ;
		}
		str = helper(check, buf, str);
	}
	return (to_return(&str));
}

/*int	main(void)
{
	int		fd;
	int		cicles = 0;
	char	*string;

	fd = open("txt.txt", O_RDONLY);
	string = get_next_line(fd);
	while (string)
	{
		printf("[]%s", string);
		free(string);
		string = get_next_line(fd);
	}
	free(string);
	return (0);
}
*/