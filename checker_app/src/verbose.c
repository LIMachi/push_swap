/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 02:42:14 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 04:34:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

int		arrow(t_actions act, int stack_mask, int color, int n)
{
	if (!color || !(stack_mask & act))
		return (L' ');
	if ((act & PUSH) && stack_mask & act && n == 0)
		return (L'P');
	if ((act & SWAP) && n < 2)
		return (L'◀');
	if (act & ROTATE)
		return (L'▲');
	if (act & RROTATE)
		return (L'▼');
	return (L' ');
}

void	verbose(t_ps_env *e, t_actions act)
{
	t_pss_node	*a;
	t_pss_node	*b;
	int			n;

	a = e->s->first;
	b = e->s[1].first;
	ft_printf("/-------------------------------\\\n| ~~~~~~~~~~ | %3s | ~~~~~~~"
	"~~~ |\n+-------------------------------+\n|       A       |       B       "
	"|\n+---------------+---------------+\n", label(act));
	n = -1;
	while (a || b)
	{
		++n;
		a ? ft_printf("| % 11d %C |", a->value, arrow(act, STAC_A, e->color, n))
			: ft_printf("|               |");
		a ? a = a->next : 0;
		b ? ft_printf(" % 11d %C |\n", b->value, arrow(act, STAC_B, e->color,
			n)) : ft_printf("               |\n");
		b ? b = b->next : 0;
	}
	ft_printf("\\-------------------------------/\n");
}
