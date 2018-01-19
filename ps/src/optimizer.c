/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:26:56 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/19 23:02:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** -1   == kill the sequence
** 0    == do nothing
** mask == apply this mask to the current sequence and kill the next
*/

inline static int			optimization(t_actions code1, t_actions code2)
{
	int				s;
	const t_actions	tab[10][3] = {{SA, SB, SS}, {SA, SS, SB}, {SB, SS, SA},
		{RA, RB, RR}, {RRA, RRB, RRR}, {PA, PB, -1}, {RA, RRA, -1},
		{RB, RRB, -1}, {SA, SA, -1}, {SB, SB, -1}};

	s = -1;
	while (++s < 10)
		if ((tab[s][0] == code1 && tab[s][1] == code2) ||
			(tab[s][0] == code2 && tab[s][1] == code1))
			return (tab[s][2]);
	return (0);
}

inline static t_act_list	*detach_sequence(t_act_list *current)
{
	t_act_list	*tmp1;
	t_act_list	*tmp2;

	tmp1 = current->prev;
	tmp2 = current->next->next;
	free(current->next);
	free(current);
	if (tmp1)
		tmp1->next = tmp2;
	if (tmp2)
		tmp2->prev = tmp1;
	return (tmp1 ? tmp1 : tmp2);
}

inline static t_act_list	*change_sequence(t_act_list *current, int mask)
{
	t_act_list	*tmp1;
	t_act_list	*tmp2;

	tmp1 = current->prev;
	tmp2 = current->next;
	free(current);
	if (tmp1)
		tmp1->next = tmp2;
	tmp2->prev = tmp1;
	tmp2->code = mask;
	return (tmp1 ? tmp1 : tmp2);
}

/*
** remove or change specific sequences of operations
*/

t_act_list					*optimizer(t_act_list *acts)
{
	int			mask;

	while (acts && acts->next)
	{
		if (!(mask = optimization(acts->code, acts->next->code)))
			acts = acts->next;
		else if (mask == -1)
			acts = detach_sequence(acts);
		else
			acts = change_sequence(acts, mask);
	}
	while (acts && acts->prev)
		acts = acts->prev;
	return (acts);
}
