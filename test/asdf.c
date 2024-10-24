/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asdf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:49:22 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/24 10:16:49 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief sort the items on stack_a using stack_b
 * 
 * The idea of double sort is to separate all items into two groups in stack_a
 * and stack_b (push_half_to_b) which are then put in order concurrently
 * (stack_a sorted increasingly, stack_b sorted decreasingly) and finally
 * joined, in order, on stack_a (push_back_to_a). There are to options to
 * proceed: either push the smallest elements of stack_a to stack_b or the
 * largest elements. Both variants are tested (op1 and op2 respectively) and are
 *  compared. The variant with the smallest number of oper- ations is returend.
 * 
 * @param stack_a stack configuration to bring in order
 * @return t_ring* list of operations to sort stack_a using stack_b
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (n > 1 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (*str1 - *str2);
}

/**
 * @brief sort the items on stack_a using stack_b
 * 
 * The idea of double sort is to separate all items into two groups in stack_a
 * and stack_b (push_half_to_b) which are then put in order concurrently
 * (stack_a sorted increasingly, stack_b sorted decreasingly) and finally
 * joined, in order, on stack_a (push_back_to_a). There are to options to
 * proceed: either push the smallest elements of stack_a to stack_b or the
 * largest elements. Both variants are tested (op1 and op2 respectively) and are
 * compared. The variant with the smallest number of oper- ations is returend.
 * 
 * @param stack_a stack configuration to bring in order
 * @return t_ring* list of operations to sort stack_a using stack_b
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (n > 1 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (*str1 - *str2);
}

/**
 * @brief sort the items on stack_a using stack_b
 * 
 * The idea of double sort is to separate all items into two groups in stack_a
 * and stack_b (push_half_to_b) which are then put in order concurrently
 * (stack_a sorted increasingly, stack_b sorted decreasingly) and finally
 * joined, in order, on stack_a (push_back_to_a). There are to options to
 * proceed: either push the smallest elements of stack_a to stack_b or the
 * largest elements. Both variants are tested (op1 and op2 respectively) and are
 * compared. The variant with the smallest number of oper- ations is returend.
 * 
 * @param stack_a stack configuration to bring in order
 * @return t_ring* list of operations to sort stack_a using stack_b
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (n > 1 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (*str1 - *str2);
}
