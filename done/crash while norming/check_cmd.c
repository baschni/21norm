/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:43:49 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 11:22:58 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file	check_cmd.c @brief	define functions to check completeness (while user
 * is breaking command over several lines) and syntax of command (after user has
*/

#include <stddef.h>

#include "libft.h"
#include "tokens.h"
#include "shell.h"

void	print_syntax_error(char *token)
{
	ft_eprintf("-%s: syntax error near unexpected token `%s'\n", \
	SHELL_NAME, token);
}

/**
 * @brief	checks if the syntax of a shell command after an opening or closing
 * bracket is correct
 *
 * Checks after an opening brackets: bracket cannot be directly followed by a
 * pipe or chain operator (excluding file pipes) or a closing bracket.
 *
 * Checks after on a closing bracket: there must be at least one non closed
 * opening bracket. If the command does continue after the closing bracket, it
 * must be followed by an pipe or chain operator, including file pipes. That
 * means it cannot be followed by a command.
 *
 * @param tokens	shell command to be checked broken into tokens
 * @param brackets	pointer to the number of brackets currently open
 * @return			1 if syntax is correct, 0 otherwise
*/
int	check_syntax_of_brackets(t_tokens *tokens, int *brackets)
{
	if (!ft_strcmp(tokens->token, "("))
	{
		(*brackets)++;
		if (tokens->next && has_operator(tokens->next->token, \
		(char *[5]){"||", "&&", "|", ";", NULL}))
			return (print_syntax_error(tokens->next->token), 0);
		if (tokens->next && !ft_strcmp(tokens->next->token, ")"))
			return (print_syntax_error(tokens->next->token), 0);
	}
	if (!ft_strcmp(tokens->token, ")"))
	{
		if (*brackets == 0)
			return (print_syntax_error(")"), 0);
		if (tokens->next && !has_operator(tokens->next->token, \
		(char *[10]){"||", "&&", "<<", ">>", \
		"|", "<", ">", ";", ")", NULL}))
			return (print_syntax_error(tokens->next->token), 0);
		(*brackets)--;
	}
	return (1);
}

/**
 * @brief	checks if the syntax of a shell command around an operator is correct
 *
 * 1) file piping operators must be followed by a filename
 *
 * 2) pipe and chain operators cannot be followed by another operator of the
 * same type
 *
 * 3) a semicolon cannot be followed by a closing bracket (todo: this is not
 * correct, e.g. (ls;))
 *
 * 4) anything else than an operator cannot be followed by an opening bracket
 *
 * @param tokens	shell command to be checked broken into tokens
 * @return			1 if syntax is correct, 0 otherwise
*/
int	check_syntax_of_operators(t_tokens *tokens)
{
	if (has_operator(tokens->token, (char *[5]){"<<", ">>", "<", ">", NULL}))
	{
		if (!tokens->next)
			return (print_syntax_error("newline"), 0);
		else if (has_operator(tokens->next->token, (char *[11]){"||", \
		"&&", "<<", ">>", "|", "<", ">", ";", "(", ")", NULL}))
			return (print_syntax_error(tokens->next->token), 0);
	}
	if (has_operator(tokens->token, (char *[5]){";", "&&", "||", "|", NULL}))
	{
		if (tokens->next && has_operator(tokens->next->token, \
		(char *[5]){"||", "&&", "|", ";", NULL}))
			return (print_syntax_error(tokens->next->token), 0);
		if (tokens->next && ft_strcmp(tokens->token, ";") && \
		!ft_strcmp(tokens->next->token, ")"))
			return (print_syntax_error(tokens->next->token), 0);
	}
	if (!has_operator(tokens->token, (char *[11]){"||", "&&", "<<", \
	">>", "|", "<", ">", ";", "(", ")", NULL}))
	{
		if (tokens->next && !ft_strcmp(tokens->next->token, "("))
			return (print_syntax_error(tokens->next->token), 0);
	}
	return (1);
}

/**
 * @brief	before parsing and executing a shell command provided by the user, it
 * will be checked if the syntax is correct
 *
 * The function will check the syntax of a command and print out a syntax error,
 *  if the syntax is not correct.
 *
 * @param tokens	shell command split up into tokens
 * @return			0 if syntax is incorrect, 1 if syntax is correct
*/
int	check_syntax(t_tokens *tokens)
{
	int	brackets;

	if (tokens && has_operator(tokens->token, \
	(char *[5]){"||", "&&", "|", ";", NULL}))
		return (print_syntax_error(tokens->token), 0);
	brackets = 0;
	while (tokens)
	{
		if (!check_syntax_of_brackets(tokens, &brackets))
			return (0);
		if (!check_syntax_of_operators(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

/**
 * @brief	checks if a shell command is complete or not and returns a separator
 * for and additional line if it's not complete
 *
 * When inserting a shell command the user might hit RETURN at any time. If the
 * command is not complete, the shell will ask to insert an additional line
 * until a complete command has been provided.
 *
 * If there are open brackets on a line and the user hits RETURN, the line break
 *  will be interpreted as if the user had entered a semicolon to separate
 * commands.
 *
 * @param tokens	user provided shell command broken up into tokens
 * @return			separator string in case the command is incomplete, NULL otherwise
*/
char	*check_completeness(t_tokens *tokens)
{
	int	brackets;

	brackets = 0;
	while (tokens->next)
	{
		if (!ft_strcmp(tokens->token, "("))
			brackets++;
		if (!ft_strcmp(tokens->token, ")"))
			brackets--;
		tokens = tokens->next;
	}
	if (!ft_strcmp(tokens->token, "("))
		brackets++;
	if (!ft_strcmp(tokens->token, ")"))
		brackets--;
	if (has_operator(tokens->token, (char *[4]){"||", "&&", "|", NULL}))
		return (ft_strdup(" "));
	if (brackets > 0)
		return (ft_strdup("; "));
	return (NULL);
}
