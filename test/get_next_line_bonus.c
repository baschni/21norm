/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:02:47 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/08 00:02:47 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
// start including only for test
#include <stdio.h>
#include <fcntl.h>
// end including only for test

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_stpcpy_strdup(char *dst, const char *src);
char	*join_list_to_str(t_rlst *start);
char	*free_list(t_rlst **rest);

t_rlst	*newline_in_list(t_rlst *rest)
{
	if (!rest)
		return (NULL);
	if (ft_strchr(rest->str, '\n'))
		return (rest);
	while (rest->next)
	{
		rest = rest->next;
		if (ft_strchr(rest->str, '\n'))
			return (rest);
	}
	return (NULL);
}

char	*add_string_to_back_of_list(t_rlst **rest, char *str)
{
	t_rlst	*new;
	t_rlst	*old;
	char	*new_str;

	new = malloc(sizeof(t_rlst));
	if (!new)
		return (free_list(rest));
	new_str = ft_stpcpy_strdup(NULL, str);
	if (!new_str)
	{
		free(new);
		return (free_list(rest));
	}
	new->str = new_str;
	new->next = (NULL);
	if (!*rest)
	{
		*rest = new;
		return (new_str);
	}
	old = *rest;
	while (old->next)
		old = old->next;
	old->next = new;
	return (new_str);
}

char	*manage_rest_and_return_newline(t_rlst **rest, char *left_over)
{
	t_rlst	*split;
	char	*s;

	split = newline_in_list(*rest);
	s = ft_strchr(split->str, '\n') + 1;
	ft_stpcpy_strdup(left_over, s);
	*s = '\0';
	s = join_list_to_str(*rest);
	free_list(rest);
	*rest = (NULL);
	return (s);
}

char	*read_to_buffer(int fd, t_rlst **rest, char *buffer, char *left_over)
{
	char	*result;
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!add_string_to_back_of_list(rest, buffer))
			return free_list(rest);
		if (ft_strchr(buffer, '\n'))
			return (manage_rest_and_return_newline(rest, left_over));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (free_list(rest));
	result = join_list_to_str(*rest);
	free_list(rest);
	if (!result)
		return (NULL);
	if (ft_strlen(result) != 0)
		return (result);
	free(result);
	return (NULL);
}

	// is it really necessary to initiate rest to an empty list?
	// if (!rest)
	// {
	// 	add_string_to_back_of_list(&rest, "");
	// 	if (!rest)
	// 		return (NULL);
	// }

/**
 * @brief Return next line of file descriptor (param fd)
 * The function is a wrapper to the library function read, with a central
 * static variable rest, which will buffer the contents of read until a new
 * line character is found or for the read contents after a newline character.
 * 
 * The function will first check for a valid file descriptor and will free the
 * static variable rest, if fd is not valid. Otherwise it will check the rest
 * for a newline character, in which case it will construct a newline of all
 * string bits until this newline and reduce the rest accordingly. If not, it
 * will allocate a buffer and launch the function read_to_buffer to read into
 * it until a newline is read, the end of the file is reached or an error
 * occurs.
 * 
 * @param 	fd		File descriptor to the file or stdin to read from.
 * 
 * @var		rest	stores the rest after a \n in between function calls
 * @var		buffer	buffer string as large as BUFFER_SIZE + 1
 * @var		result	return value of function read_to_buffer
 * 
 * @return 	char* 	returns every character until the next \n in the fd.
 */
char	*get_next_line(int fd)
{
	static char		left_over[MAX_OPEN_FILES][BUFFER_SIZE + 1];
	t_rlst			  *no_newline;
	char			*buffer;
	char			*result;

	no_newline = (NULL);
	if (!add_string_to_back_of_list(&no_newline, left_over[fd]))
		return (NULL);
	left_over[fd][0] = '\0';
	if (newline_in_list(no_newline))
		return (manage_rest_and_return_newline(&no_newline, left_over[fd]));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		if (no_newline)
			return (free_list(&no_newline));
		return (NULL);
	}
	result = read_to_buffer(fd, &no_newline, buffer, left_over[fd]);
	free(buffer);
	return (result);
}

// int main()
// {
//     int fd;
//     fd = open("variable_nls.txt", O_RDONLY);
//     char *line;
//     while((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//         free(line);
//     }
//     return (0);
// }