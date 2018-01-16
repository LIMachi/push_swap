/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:53:40 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 19:24:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** basic set of instructions
*/

inline static int	swap(t_pss *stack, t_pss *unused)
{
	t_pss_node	*tmp;

	(void)unused;
	if (stack->size < 2)
		return (-1);
	tmp = stack->first;
	stack->first = tmp->next;
	stack->first->prev = NULL;
	tmp->prev = stack->first;
	tmp->next = stack->first->next;
	stack->first->next = tmp;
	return (0);
}

inline static int	rotate(t_pss *stack, t_pss *unused)
{
	t_pss_node	*tmp;

	(void)unused;
	if (stack->size < 2)
		return (-1);
	tmp = stack->first;
	stack->first = tmp->next;
	stack->first->prev = NULL;
	tmp->prev = stack->last;
	tmp->next = NULL;
	stack->last->next = tmp;
	stack->last = tmp;
	return (0);
}

inline static int	rrotate(t_pss *stack, t_pss *unused)
{
	t_pss_node	*tmp;

	(void)unused;
	if (stack->size < 2)
		return (-1);
	tmp = stack->last;
	stack->last = tmp->prev;
	stack->last->next = NULL;
	tmp->prev = NULL;
	tmp->next = stack->first;
	stack->first->prev = tmp;
	stack->first = tmp;
	return (0);
}

inline static int	push(t_pss *from, t_pss *to)
{
	t_pss_node	*tmp;

	if (from->size == 0)
		return (-1);
	tmp = from->first;
	from->first = tmp->next;
	from->first->prev = NULL;
	if (to->size > 0)
	{
		tmp->next = to->first;
		to->first->prev = tmp;
	}
	else
		tmp->next = NULL;
	--from->size;
	++to->size;
	to->first = tmp;
	return (0);
}

int					action(t_ps_env *e, t_actions act)
{
	int		r;
	int		s;

	r = 0;
	s = 0;
	while (!r && (act & (STAC_A | STAC_B)))
	{
		if (act & STAC_A)
			act ^= STAC_A;
		else
			s = 1;
		if (act & SWAP)
			r |= swap(&e->s[s], NULL);
		if (act & ROTATE)
			r |= rotate(&e->s[s], NULL);
		if (act & RROTATE)
			r |= rrotate(&e->s[s], NULL);
		if (act & PUSH)
			r |= push(&e->s[s], &e->s[s ^ 1]);
	}
	printf("r status: %d\naction: %d\n", r, act);
	if (e->tmp_sort && !r)
		queue_action(e, act);
	return (r);
}
