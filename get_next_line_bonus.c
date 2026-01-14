/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmanett <frmanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:34:47 by frmanett          #+#    #+#             */
/*   Updated: 2026/01/14 17:22:11 by frmanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*str[4096];

	if (fd < 0)
		return (NULL);
	check = 1;
	while (check && !ft_strchr(str[fd], '\n'))
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
			return (free (buf), NULL);
		if (check == 0 && !str[fd])
		{
			free (buf);
			break ;
		}
		str[fd] = helper(check, buf, str[fd]);
	}
	return (to_return(&str[fd]));
}

/*int	main(void)
{
	int		fd;
	int		fd2;
	char	*string;
	char	*string2; 
	
	fd = open("../../txt.txt", O_RDONLY);
	fd2 = open("../../txts.txt", O_RDONLY);
	string = get_next_line(fd);
	string2 = get_next_line(fd2);
	while (string || string2)
	{
		if (string)
			printf("1.%s", string);
		if (string2)
			printf("2.%s", string2);
		free(string);
		free(string2);
		string = get_next_line(fd);
		string2 = get_next_line(fd2);
	}
	free(string);
	return (0);
}*/
