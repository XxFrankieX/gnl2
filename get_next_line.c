/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconde-s <mconde-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:12:15 by mconde-s          #+#    #+#             */
/*   Updated: 2024/12/10 19:21:13 by mconde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len > __SIZE_MAX__)
		len = __SIZE_MAX__;
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	sub = malloc((len * sizeof(char)) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, (s + start), len + 1);
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*result;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	result = malloc(lens1 + lens2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, lens1);
	ft_memcpy(result + lens1, s2, lens2 + 1);
	return (result);
}

char	*ft_line(char *buffer, char *line, char **temp, char *tmp)
{
	size_t	i;

	i = 0;
	(void)tmp;
	//line -> *tmp("0")
	if (buffer)
	{
		tmp = ft_strjoin(*temp, buffer);
		free(*temp);
		free(buffer);
		*temp = tmp;
	}
	while (*temp && (*temp)[i] != '\0' && (*temp)[i] != '\n')
		i++;
	//line -> *tmp("0") + buffer"" de 0 a i
	if (*temp && **temp)
	{
		line = ft_substr(*temp, 0, i + 1);
		if (!line)
			return (free(*temp), NULL);
		tmp = ft_substr(*temp, i + 1, ft_strlen(*temp));
		free(*temp);
		*temp = tmp;
	}
	 else if (!**temp)
	 	*temp = (free(*temp), NULL);
	return (line);
}

char	*ft_read(int fd, char **result)
{
	char	*buffer;
	char	*line;
	char	*tmp;
	ssize_t	nbr;

	nbr = 1;
	line = ft_strdup("");
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(line), NULL);
	buffer[0] = '\0';
	while (1)
	{
		nbr = read(fd, buffer, BUFFER_SIZE);
		if (nbr < 0)
			return (free(buffer), free(line), NULL);
		if (nbr == 0)
			return (*result = (free(buffer), line), *result);
		buffer[nbr] = '\0';
		tmp = ft_strjoin(line, buffer);
		line = (free(line), tmp);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (*result = (free(buffer), line), *result);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	char		*buffer;
	static char	*temp = NULL;

	line = NULL;
	buffer = NULL;
	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_read(fd, &buffer))
	{
		temp = (free(buffer), free(temp), NULL);
		return (NULL);
	}
	else
		line = ft_line(buffer, line, &temp, tmp);
	return (line);
}

#include <string.h>

void gnl(int fd, char * expectedReturn)
{
	char *  gnlReturn = get_next_line(fd);
	if (expectedReturn == NULL)
		printf("%s", gnlReturn);
	else if (!strcmp(gnlReturn, expectedReturn))
		printf("%s", gnlReturn);
	free(gnlReturn);
}

int	main(void)
{
	// int fd = open("41_with_nl", O_RDONLY);
	// int fd = 35;//open("get_next_line.c", O_RDONLY);
	// if (fd < 0)
	// 	printf("error al abrir el archivo");

	int fd = open("gnlTester/files/nl", O_RDWR);
	 gnl(fd, "\n");
	 gnl(fd, NULL);
	close(fd);

	return (0);
} 