/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 00:51:13 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/17 03:34:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** simple in set instructions to make a basic switch
*/

int		mini_sort(t_ps_env *env, t_pss *stack)
{
	t_pss_node	*node;

	node = stack->first->next;
	if (stack->size > 1 && stack->first->value * stack->order >
			node->value * stack->order)
		action(env, stack->mask | SWAP);
	if (stack->size > 2 && node->value * stack->order >
			node->next->value * stack->order)
	{
		action(env, stack->mask | ROTATE);
		action(env, stack->mask | SWAP);
		action(env, stack->mask | RROTATE);
	}
	if (stack->size > 1 && stack->first->value * stack->order >
			node->value * stack->order)
		action(env, stack->mask | SWAP);
	return (0);
}
