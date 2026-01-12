/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmanett <frmanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:52:49 by frmanett          #+#    #+#             */
/*   Updated: 2026/01/12 18:43:16 by frmanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_line(int fd)
{
	char		*buf;
	ssize_t		check;
	static char	*str;

	check = 1;
	while (check && !ft_strchr(str, '\n'))
	{	
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		buf[BUFFER_SIZE] = '\0';
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
		{
			free (buf);
			return (NULL);
		}
		str = ft_strjoin(str, buf);
		free (buf);
	}
	return (str);
}
// NUF = 5
// ciao a tutti

// buf = ciao a tut

char	*get_next_line(int fd)
{
	char *line;

	if (fd < 0)
		return (NULL);
	line = find_line(fd);
	printf("%s", line);
	return (NULL);
}

int main()
{
	int	fd;
	int cicles = 0;
	char	*string;

	fd = open("txt.txt", O_RDONLY);
	while(cicles < 1)
	{
		string = get_next_line(fd);
		//printf("stringa = %s\n", string);
		free(string);
		cicles++;
	}
	return(0);
}

/*Upon successful completion, these functions shall return a non-negative
       integer indicating the number of bytes actually  read.  Otherwise,  the
       functions shall return -1 and set errno to indicate the error.
*/