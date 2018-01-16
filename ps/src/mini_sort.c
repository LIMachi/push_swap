/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 00:51:13 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 01:36:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		mini_sort(t_ps_env *env, t_pss *stack)
{
	t_pss_node	*node;

	node = stack->first->next;
	if (stack->size > 1 && stack->first->value * stack->order < node->value)
		action(env, stack->mask | SWAP);
	if (stack->size > 2 && node->value * stack->order < node->next->value)
	{
		action(env, stack->mask | ROTATE);
		action(env, stack->mask | SWAP);
		action(env, stack->mask | RROTATE);
	}
	if (stack->size > 1 && stack->first->value * stack->order < node->value)
		action(env, stack->mask | SWAP);
}
