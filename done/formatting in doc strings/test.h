/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:42:17 by blucken           #+#    #+#             */
/*   Updated: 2025/02/25 19:16:40 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

/**
 * @brief	types for pipe modifiers asd qwer qwefsd zxcvz vzxcv zx fa sdf  asdf
 * 			f asdf asdf asdf asdf asdf asdf asdf asdf asdf asdf asd f asdf asdf
 * 			asdf asdf asdf asdf asdf
 * @bri		types for pipe modifiers asd qwer qwefsd zxcvz vzxcv zx fa sdf  asdf
 * 			f asdf asdf asdf asdf asdf asdf asdf asdf asdf asdf asd f asdf asdf
 * 			asdf asdf asdf asdf asdf
 *
 * @param tokens	shell command to be checked broken into r pipe modifiers asd
 * 					qwer qwefsd zxcvz vzxcv zx fa sr pipe modifiers asd qwer
 * 					qwefsd zxcvz vzxcv zx fa sr pipe modifiers asd qwer qwefsd
 * 					zxcvz vzxcv zx fa stokens
 * @param brackets	pointer to the number of brackets currently open
 * @return			1 if syntax is correct, 0 otherwise
*/

typedef enum e_mtype
{
	NONE,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	HEREDOC
}	t_mtype;

#endif