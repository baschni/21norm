/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:26:40 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 12:20:33 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdbool.h>

typedef struct s_history	t_history;
typedef struct s_shell		t_shell;

typedef struct s_history
{
	char				*line;
	size_t				index;
	struct s_history	*next;
}	t_history;

typedef struct s_history_data
{
	int		fd;
	int		i;
	char	*ln;
	char	*sp;
	char	*prev_id_str;
	int		prev_line_id;
}	t_history_data;

typedef struct s_shell		t_shell;

// history.c
bool	manage_history(t_shell *shell, char *line);
int		ft_history(t_args *args, int fd_out, t_shell *shell);

// history_utils.c
void	ft_historyaddback(t_history *history, t_history *new);
size_t	ft_historysize(t_history *history);
size_t	find_index_size(size_t index);
size_t	count_file_lines(const char *filename);

//update_history_file.c
void	old_history_update(t_shell *shell);
void	update_history_file(t_shell *shell);
bool	update_history(t_shell *shell, char *line);

#endif