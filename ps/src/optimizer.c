/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 01:26:56 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/17 16:50:16 by hmartzol         ###   ########.fr       */
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

t_act_list			*optimizer(t_act_list *acts, int *run)
{
	t_act_list	*tmp;
	t_act_list	*last;
	t_act_list	*out;
	int			mask;

	out = NULL;
	last = NULL;
	*run = 0;
	while (run && acts && acts->next)
		if ((mask = complement(acts->code, acts->next->code)) != -1)
		{
			if (out == NULL)
				out = acts;
			if (mask)
			{
				*run = 1;
				acts->code = mask;
				tmp = acts->next->next;
				free(acts->next);
				acts->next = tmp;
			}
			last = acts;
			acts = acts->next;
		}
		else
		{
			*run = 1;
			tmp = acts->next->next;
			if (last)
				last->next = tmp;
			free(acts->next);
			free(acts);
			acts = tmp;
		}
	return (out);
}
