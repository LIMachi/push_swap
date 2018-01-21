/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:27:07 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/20 03:19:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

const char	*label(t_actions act)
{
	int			i;
	int			t;
	const char	*tab[6][3] = {{"sb", "sa", "ss"}, {"rb", "ra", "rr"},
		{"rrb", "rra", "rrr"}, {"pb", "pa", "(invalid) pp"},
		{"vb", "va", "vv"}, {"db", "da", "dd"}};

	t = 0b111111 & act;
	i = 0;
	while (t >>= 1)
		++i;
	return (tab[i][((act & 0b11000000) >> 6) - 1]);
}

/*
** unpile a set of code of instruction and print them in reverse order
** (first element will be print last)
*/

void		printer(t_act_list *acts, int fd)
{
	while (acts->next)
		acts = acts->next;
	while (acts)
	{
		ft_dprintf(fd, "%s\n", label(acts->code));
		acts = acts->prev;
	}
}
