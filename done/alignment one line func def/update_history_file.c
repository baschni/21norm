/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:41:45 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 12:00:47 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

#include "cmd.h"
#include "libft.h"
#include "debug.h"
#include "shell.h"
#include "history.h"

#define BUF_SIZE 65536

/**
 * @file update_history_file.c @brief Handles shell command history management
 * and persistence @details This file contains functions for managing the
 * shell's command history, including reading from and writing to a history
*/

static t_history	*find_history_start(t_shell	*shell);
static void			process_history_buffer(t_shell *shell, char *buf, \
ssize_t	bytes);

/**
 * @brief Updates shell history from existing history file
 * @param shell Pointer to the shell structure
 * @details Reads the history file in chunks and processes each line to update
 * the shell's command history. If the file cannot be opened, silently returns.
*/
void	old_history_update(t_shell *shell)
{
	int		fd;
	char	buf[BUF_SIZE];
	ssize_t	bytes;

	if (!shell)
		return ;
	fd = open("tmp/.minishell_history", O_RDONLY);
	if (fd < 0)
		return ;
	bytes = read(fd, buf, BUF_SIZE);
	while (bytes > 0)
	{
		process_history_buffer(shell, buf, bytes);
		bytes = read(fd, buf, BUF_SIZE);
	}
	close(fd);
}

/**
 * @brief Writes current history to the history file
 * @param shell Pointer to the shell structure
 * @details Appends new history entries to the history file. Only writes entries
 * that aren't already present in the file. Creates the file if it doesn't exist.
*/
void	update_history_file(t_shell *shell)
{
	int			fd;
	t_history	*current;

	if (!shell || !shell->history)
		return ;
	if (mkdir("tmp", 0755) == -1 && errno != EEXIST)
		return ;
	fd = open("tmp/.minishell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return ;

	current = find_history_start(shell);
	while (current)
	{
		if (current->line && current->line[0])
		{
			write(fd, current->line, ft_strlen(current->line));
			write(fd, "\n", 1);
		}
		current = current->next;
	}
	close(fd);
}

/**
 * @brief Adds a new entry to the shell's history
 * @param shell Pointer to the shell structure
 * @param line Command line to add to history
 * @return true if successful, false if memory allocation fails
 * @details Allocates and initializes a new history entry, adding it to the
 * shell's history list. Updates the entry's index based on its position.
*/
bool	update_history(t_shell *shell, char *line)
{
	t_history	*history;

	if (!shell || !line)
		return (false);
	if (!set(&history, malloc(sizeof(t_history))))
		return (false);
	history->line = ft_strdup(line);
	if (!history->line)
	{
		free(history);
		return (false);
	}
	history->next = NULL;
	if (!shell->history)
		shell->history = history;
	else
		ft_historyaddback(shell->history, history);
	history->index = ft_historysize(shell->history);
	return (true);
}

/**
 * @brief Finds the starting point for new history entries
 * @param shell Pointer to the shell structure
 * @return Pointer to the first new history entry to be written
 * @details Determines where new history entries should begin by counting existing
 * file lines and moving through the history list accordingly.
*/
static t_history	*find_history_start(t_shell *shell)
{
	t_history	*current;
	size_t		count;

	if (!shell || !shell->history)
		return (NULL);
	count = count_file_lines("tmp/.minishell_history");
	current = shell->history;
	while (current && count > 0)
	{
		current = current->next;
		count--;
	}
	return (current);
}

/**
 * @brief Processes a buffer of history data
 * @param shell Pointer to the shell structure
 * @param buf Buffer containing history data
 * @param bytes Number of bytes in the buffer
 * @details Parses the buffer line by line, adding each line to the shell's
 * history. Handles buffer boundaries and ensures proper line termination.
*/
static void	process_history_buffer(t_shell *shell, char *buf \
, ssize_t bytes)
{
	char	line[BUF_SIZE];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < bytes)
	{
		if (buf[i] == '\n')
		{
			line[j] = '\0';
			if (j > 0 && *line)
			{
				char *tmp = line;
				if (tmp)
				{
					add_history(tmp);
					if (!update_history(shell, tmp))
						tmp = NULL;
					else
						tmp = NULL;
				}
			}
			j = 0;
		}
		else if (j < BUF_SIZE - 1)
			line[j++] = buf[i];
		i++;
	}
}
