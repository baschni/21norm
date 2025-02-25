/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testtab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:43:49 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 11:22:59 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_syntax_of_brackets(t_tokens *tokens, int *brackets)
{
	if (tokens->next && !has_operator(tokens->next->token, \
	(char *[10]){"||", "&&", "<<", ">>", \
	"|", "<", ">", ";", ")", NULL}))
		return (print_syntax_error(tokens->next->token), 0);
}
