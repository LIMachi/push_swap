/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:53:40 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 02:42:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

/*
** basic set of instructions
*/

inline static int	swap(t_pss *stack, t_pss *unused)
{
	int64_t	t;

	(void)unused;
	if (stack->size < 2)
		return (-1);
	t = stack->first->value;
	stack->first->value = stack->first->next->value;
	stack->first->next->value = t;
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
	tmp->next = stack->first;
	tmp->prev = NULL;
	stack->first->prev = tmp;
	stack->first = tmp;
	return (0);
}

inline static int	push(t_pss *from, t_pss *to)
{
	t_pss_node	*tmp;

	if (from->size == 0)
		return (-1);
	if (from->size == 1)
	{
		from->first->next = to->first;
		to->first = from->first;
		from->first = NULL;
		from->last = NULL;
		++to->size;
		return (from->size = 0);
	}
	tmp = from->first;
	from->first = from->first->next;
	from->first->prev = NULL;
	if (--from->size == 1)
		from->last = from->first;
	if (to->size++)
		to->first->prev = tmp;
	else
		to->last = tmp;
	tmp->next = to->first;
	to->first = tmp;
	return (0);
}

void				action(t_ps_env *e, t_actions act)
{
	int		r;
	int		s;
	int		m;

	r = 0;
	s = 0;
	m = act;
	while (!r && s < 2 && (m & (STAC_A | STAC_B)))
	{
		if (m & STAC_A)
			m ^= STAC_A;
		else
			s = 1;
		if (m & SWAP)
			r |= swap(&e->s[s], NULL);
		if (m & ROTATE)
			r |= rotate(&e->s[s], NULL);
		if (m & RROTATE)
			r |= rrotate(&e->s[s], NULL);
		if (m & PUSH)
			r |= push(&e->s[s ^ 1], &e->s[s]);
		++s;
	}
	if (e->verbose)
		verbose(e, act);
}
