/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 03:24:36 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 03:24:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

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
