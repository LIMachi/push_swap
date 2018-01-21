/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:20:19 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/20 03:54:00 by hmartzol         ###   ########.fr       */
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

	if (e->verbose)
		ft_dprintf(2, "[action]: queueing action: '%s'\n", label(act));
	if ((tmp = (t_act_list*)malloc(sizeof(t_act_list))) == NULL)
		exit(_(ft_printf("Can't queue an action, malloc failed\n"), 4));
	tmp->code = act;
	tmp->next = e->acts;
	tmp->prev = NULL;
	if (e->acts)
		e->acts->prev = tmp;
	e->acts = tmp;
}
