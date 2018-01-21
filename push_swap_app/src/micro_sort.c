/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:36:05 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/18 00:39:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** specific sort for 0 to 3 elements
** 1 2 3 |
** 1 3 2 | ra sa rra
** 2 1 3 | sa
** 3 1 2 | ra
** 2 3 1 | rra
** 3 2 1 | ra sa
** 1 2   |
** 2 1   | sa
** 1     |
**       |
*/

void	micro_sort(t_ps_env *env)
{
	t_pss_node	*p;

	p = env->node_head;
	if (env->s->size < 2 || (env->s->size == 2 && p[0].value < p[1].value) ||
			(p[0].value < p[1].value && p[1].value < p[2].value))
		return ;
	if (env->s->size == 2)
		action(env, SA);
	else if (p[0].value < p[2].value && p[2].value < p[1].value)
	{
		action(env, RA);
		action(env, SA);
		action(env, RRA);
	}
	else if (p[2].value < p[1].value && p[1].value < p[0].value)
	{
		action(env, RA);
		action(env, SA);
	}
	else if (p[1].value < p[0].value && p[0].value < p[2].value)
		action(env, SA);
	else if (p[1].value < p[2].value && p[2].value < p[0].value)
		action(env, RA);
	else
		action(env, RRA);
}
