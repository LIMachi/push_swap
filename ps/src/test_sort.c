/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:35:36 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 01:35:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int		test_sort(t_ps_env *env)
{
	t_pss_node	*node;

	if (env->s[1].size)
		return (0);
	if (env->s[0].size < 2)
		return (1);
	node = env->s[0].first;
	while (node->next)
	{
		if (node->value > node->next->value)
			return (0);
		node = node->next;
	}
	return (1);
}
