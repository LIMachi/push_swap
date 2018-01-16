/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:20:19 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 01:26:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	queue_action(t_ps_env *e, t_actions act)
{
	t_act_list	*tmp;

	if (tmp = malloc(sizeof(t_act_list)))
		return ;
	tmp->code = act;
	tmp->next = e->acts;
	e->acts = tmp;
}
