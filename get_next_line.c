/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmanett <frmanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:52:49 by frmanett          #+#    #+#             */
/*   Updated: 2026/01/13 19:16:36 by frmanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *set_static(char *str)
{
	int		i;
	char	*sstr;
	int		j;

	i = 0;
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
		sstr[j] = str [i];
		j--;
		i--;
	}
	free (str);
	return (sstr);
}

static char	*copy_line(char *str)
{
	int	i;
	char *ret;
	
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

static char	*find_line(int fd)
{
	char		*buf;
	ssize_t		check;
	static char	*str = NULL;
	char		*temp;
	
	check = 1;
	while (check && !ft_strchr(str, '\n'))
	{	
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
		{
			free (buf);
			return (NULL);
		}
		if (check == 0 && !str)
		{
			free (buf);
			break;
		}
		buf[check] = '\0';
		temp = ft_strjoin(str, buf, -1, 0);
		free (str);
		str = temp;
		free (buf);
	}
	if (check == BUFFER_SIZE)
	{
		temp = copy_line(str);
		str = set_static(str);
		return (temp);	
	}
	else if(str)
	{
		//write(1, "usdgk", 6);
		temp = ft_strdup(str);
		free(str);
		str = NULL;
		return (temp);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char *line;

	if (fd < 0)
		return (NULL);
	line = find_line(fd);
	return (line);
}

/* int main()
{
	int	fd;
	int cicles = 0;
	char	*string;

	fd = open("txt.txt", O_RDONLY);
	string = get_next_line(fd);
	while(string)
	{
		printf("%s", string);
		free(string);
		string = get_next_line(fd);
	}
	free(string);
	return(0);
} */

/*Upon successful completion, these functions shall return a non-negative
       integer indicating the number of bytes actually  read.  Otherwise,  the
       functions shall return -1 and set errno to indicate the error.
*/