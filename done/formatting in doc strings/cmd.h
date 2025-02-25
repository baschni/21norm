/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:42:17 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 19:24:58 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

/**
 * @brief	types for pipe modifiers asd qwer qwefsd zxcvz vzxcv zx fa sdf
 * 			asdf f asdf asdf asdf asdf asdf asdf asdf asdf asdf asdf asd f
 * 			asdf asdf asdf asdf asdf asdf asdf
 *
 * @bri		types for pipe modifiers asd qwer qwefsd zxcvz vzxcv zx fa sdf
 * 			asdf f asdf asdf asdf asdf asdf asdf asdf asdf asdf asdf asd f
 * 			asdf asdf asdf asdf asdf asdf asdf
 *
 * @param tokens	shell command to be checked broken into r pipe modifiers
 * 					asd qwer qwefsd zxcvz vzxcv zx fa sr pipe modifiers asd
 * 					qwer qwefsd zxcvz vzxcv zx fa sr pipe modifiers asd qwer
 * 					qwefsd zxcvz vzxcv zx fa stokens
 * @param brackets	pointer to the number of brackets currently open
 * @return			1 if syntax is correct, 0 otherwise
*/

/**
 * @brief			types for pipe modifiers asdf asdf asdf asdf asdf asdf
 * 					asdf asdf asdf asdf asdf asd f
 *
 * @enumzxcvzxcv	e_mtype
*/
typedef enum e_mtype
{
	NONE,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	HEREDOC
}	t_mtype;

/**
 * @brief	holds type of modifier and its argument
 *
 * The argument will be the delimiter for heredoc or the filename otherwise
 *
** <<	delimiter	ask user for heredoc input until *delimiter* or ctrl + D
** <	filename	replace STDIN with contents of *filename*
 * >  filename		write STDOUT into *filename* >> filename		append
 * STDOUT into *filename*
 *
*/
typedef struct s_mod
{
	t_mtype	type;
	char	*arg;
}	t_mod;

/**
 * @brief	a list of modifiers
 *
 * minishell will use this structure to parse and store the mods for STDIN and
 * the ones for STDOUT. In bash only the last modifier in the command line will
 * actually be bound to STDIN or STDOUT.
 *
*/
typedef struct s_mods
{
	t_mod			*mod;
	struct s_mods	*next;
}	t_mods;

/**
 * @brief	holds a list of the arguments supplied on a command line
 *
*/
typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}	t_args;

/**
 * @brief	will hold the cmd name, its arguments and all pipe modifiers of a
 * 			command line without pipes
 *
 * example: < file1 < file2 cat << EOF >> file3 > file4 file5 file6
 *
*/
typedef struct s_cmd
{
	char	*name;
	char	*cmd_path;
	t_args	*args;
}	t_cmd;

// pipe structure will not be needed anymore because it will be integrated into the binary tree
// /**
//  * @brief holds a list of commands separated by pipes
//  *
//  * example: < file1 cat | cat > file2
//  *
//  * when correctly parsed, the pipe structure for the example will result in a
//  * list of to cmd structures holding the left or the right part of the |
//  * character respectively.
//  *
// */
// typedef struct s_pipe
// {
// 	t_cmd			*cmd;
// 	struct s_pipe	*next;
// }	t_pipe;

int		parse_name_and_args(t_cmd *cmd, char *str);

#endif