/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:20:19 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 18:52:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** pushes (on the top, queue can be missleading) a new instruction code on a
** stack to be later optimized and printed (print in reverse order)
*/

void	queue_action(t_ps_env *e, t_actions act)
{
	t_act_list	*tmp;

	if ((tmp = malloc(sizeof(t_act_list))) == NULL)
		return ;
	tmp->code = act;
	tmp->next = e->acts;
	e->acts = tmp;
}
