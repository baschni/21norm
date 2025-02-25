/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:55:11 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/25 19:25:21 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef _21NORMER_TMP_H
# define _21NORMER_TMP_H

# include "cmd.h"

/**
 * @brief	type of the node in the cmd binary tree
 *
 * COMMAND				command without pipes or control structures, but with
 * modifiers. e.g. "< file_in cat > file_out" PIPE					| CHAIN
 * ; CHAIN_ON_SUCCESS		&& CHAIN_ON_FAIL		||
 *
*/
typedef enum e_ntype
{
	UNKNOWN_TYPE,
	COMMAND,
	PIPE,
	CHAIN,
	CHAIN_ON_SUCCESS,
	CHAIN_ON_FAIL,
	SUBSHELL
}	t_ntype;

/**
 * @brief	content for a cmd binary tree
 *
 * The node content will hold the type of the node operator/command and if of
 * type command, the completely parsed command incl. arguments and modifiers
 *
*/
typedef struct s_node
{
	t_ntype	type;
	t_mods	*mods;
	t_cmd	*cmd;
}	t_node;

/**
 * @brief	binary tree with a left leaf and a right leaf
 *
 * The structure is a node in the binary tree, with a pointer to the left subnode
 * and the right subnode
 *
*/
typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

/**
 * @brief	binary tree with a left leaf and a right leaf
 *
 * The structure is a node in the binary tree, with a pointer to the left subnode
 * and the right subnode
 *
*/
typedef struct s_ctree
{
	t_node			*node;
	struct s_ctree	*left;
	struct s_ctree	*right;
}	t_ctree;

#endif