/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:33:58 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 11:25:15 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "debug.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"

#ifndef DEBUG_EXECUTE_CMD
# define DEBUG_EXECUTE_CMD 0
#endif

static void		check_access(t_cmd *cmd, char *cmd_path, t_shell *shell);
static pid_t	exec_parent_builtin(int fd_out, t_node	*node, \
	t_shell *shell, t_builtin *builtin);
static void		execve_cmd(char *cmd_path, char **args_tabs, t_shell *shell);

pid_t	execute_cmd(t_node *node, int fd_in, int fd_out, t_shell *shell)
{
	pid_t		pid;
	char		*cmd_path;
	char		**args_tabs;
	t_builtin	*builtin;

	builtin = in_builtins(node->cmd->name, shell->builtins);
	if (builtin)
		return (exec_parent_builtin(fd_out, node, shell, builtin));
	pid = fork();
	if (pid < 0)
		return (fork_error());
	cmd_path = NULL;
	args_tabs = NULL;
	if (pid == 0)
	{
		if (!expand_vars(node, shell))
			exit(1);
		apply_modifiers(node->mods, &fd_in, &fd_out);
		cmd_path = get_cmd_path(node->cmd->name, shell);
		check_access(node->cmd, cmd_path, shell);
		args_tabs = args_list_to_tab(node->cmd);
		if (!args_tabs)
			args_tab_error(cmd_path, shell);
		if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
			dup2_error(cmd_path, args_tabs, shell);
		close_all_pipes_except(fd_in, fd_out, shell->pipes);
		execve_cmd(cmd_path, args_tabs, shell);
	}
	return (pid);
}

static void	check_access(t_cmd *cmd, char *cmd_path, t_shell *shell)
{
	if (access(cmd_path, X_OK) == -1)
	{
		write(STDERR_FILENO, "-", 1);
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd->name, ft_strlen(cmd->name));
		write(STDERR_FILENO, ": command not found\n", 20);
		if (DEBUG_EXECUTE_CMD)
		{
			print_debug("command not found :");
			print_debug(cmd->name);
		}
		free(cmd_path);
		free_shell(shell);
		exit(EXIT_CMD_NOT_FOUND);
	}
}

static pid_t	exec_parent_builtin(int fd_out, t_node	*node, t_shell *shell, \
	t_builtin *builtin)
{
	if (!expand_vars(node, shell))
		return (-1);
	return (builtin->func(node->cmd->args, fd_out, shell));
}

static void	execve_cmd(char *cmd_path, char **args_tabs, t_shell *shell)
{
	execve(cmd_path, args_tabs, shell->env);
	perror("execve");
	free(cmd_path);
	ft_free_splits(args_tabs);
	free_shell(shell);
	exit(EXIT_CMD_NOT_EXECUTABLE);
}
