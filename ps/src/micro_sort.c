/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:36:05 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 19:21:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** specific sort for 0 to 3 elements
*/

void	micro_sort(t_ps_env *env)
{
	t_pss_node	*node;

	node = env->s->first;
	while (!test_sort(env))
		if (node->value > node->next->value)
		{
			if (env->s->size > 2 && node->value < env->s->last->value)
				action(env, SA);
			else
				action(env, RA);
		}
		else if (env->s->size > 2 && node->value > env->s->last->value)
			action(env, RRA);
		else
			action(env, RA);
}
