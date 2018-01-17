/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:26:56 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/17 03:25:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** -1   == kill the sequence
** 0    == do nothing
** mask == apply this mask to the current sequence and kill the next
** return logic: 1 ^ 2 == 3; 1 ^ 3 == 2; 2 ^ 3 == 1;
** -1 in tab should never match any mask
*/

inline static int	complement(t_actions code1, t_actions code2)
{
	int				i;
	int				j;
	int				s;
	const t_actions	tab[8][3] = {{SA, SB, SS}, {RA, RB, RR}, {RRA, RRB, RRR},
		{PA, PB, -1}, {RA, RRA, -1}, {RB, RRB, -1}, {SA, SA, -1}, {SB, SB, -1}};

	s = -1;
	while (++s < 8)
	{
		i = -1;
		while (++i < 3 && tab[s][i] != code1)
			;
		if (i < 3)
		{
			j = -1;
			while (i == ++j || (j < 3 && tab[s][j] != code2))
				;
			if (j < 3)
				return (tab[s][((i + 1) ^ (j + 1)) - 1]);
		}
	}
	return (0);
}

/*
** acts = acts->next; jumps the head instruction because i'm lazy and don't want
** to mess with changing the first action of env
*/

void				optimizer(t_act_list *acts)
{
	t_act_list	*tmp;
	int			mask;

	acts = acts ? acts->next : NULL;
	while (acts && acts->next)
	{
		if (!(mask = complement(acts->code, acts->next->code)))
		{
			acts = acts->next;
			continue ;
		}
		tmp = acts->next->next;
		free(acts->next);
		acts->next = tmp;
		if (mask == -1)
		{
			tmp = acts->next;
			free(acts);
			acts = tmp;
			continue ;
		}
		else
			acts->code = mask;
		acts = acts->next;
	}
}
