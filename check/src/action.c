/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 06:00:40 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/13 20:16:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	rb_action(t_ps_env *e, int act)
{
	int		t;
	size_t	i;

	if ((RB | RRB) & act && e->b.m > e->b.s - 1)
		return (1);
	if (RRB & act)
	{
		i = e->b.s;
		t = e->b.d[e->b.s - 1];
		while (--i > e->b.m)
			e->b.d[i] = e->b.d[i - 1];
		e->b.d[i] = t;
	}
	if (RB & act)
	{
		i = e->b.m;
		t = e->b.d[i];
		while (++i < e->b.s)
			e->b.d[i - 1] = e->b.d[i];
		e->b.d[i - 1] = t;
	}
	return (0);
}

int	ra_action(t_ps_env *e, int act)
{
	int		t;
	size_t	i;

	if ((RA | RRA) & act && e->b.m < 2)
		return (1);
	if (RA & act)
	{
		i = e->b.m;
		t = e->b.d[i - 1];
		while (--i)
			e->b.d[i] = e->b.d[i - 1];
		e->b.d[i] = t;
	}
	if (RRA & act)
	{
		i = 0;
		t = e->b.d[0];
		while (i++ < e->b.m - 1)
			e->b.d[i - 1] = e->b.d[i];
		e->b.d[i - 1] = t;
	}
	return (0);
}

// int	print_action(t_ps_env *e, int act)
// {
// 	int				t;
// 	int				sa;
// 	int				sb;
// 	size_t			i;
// 	const wchar_t	c[] = L"┌┐└┘├┤┬┴┼│───────────────\0               ";
// 	// char			line[32];
//
// 	sa = 0;
// 	sb = 0;
// 	if ((i = e->b.m) && (VA & act || (e->opt & VERBOSE)))
// 		while (--i != (size_t)-1)
// 			_(t = ft_evaluate_i128_size(e->b.d[i]),
// 				sa = t > sa ? t : sa);
// 	i = e->b.m - 1;
// 	if (VB & act || (e->opt & VERBOSE))
// 		while (++i < e->b.s)
// 			_(t = ft_evaluate_i128_size(e->b.d[i]),
// 				sb = t > sb ? t : sb);
// 	sa = sa + !(sa & 1);
// 	sb = sb + !(sb & 1);
// 	if (sa || sb)
// 	{
// 		ft_printf("┌%S┬%S┐\n", &c[23 - sa], &c[23 - sb]);
// 		ft_printf("│%S A %S│%S B %S│\n", &c[41 - sa / 2], &c[41 - sa / 2],
// 			&c[41 - sb / 2], &c[41 - sb / 2]);
// 		ft_printf("├%S┼%S┤\n", &c[23 - sa], &c[23 - sb]);
// 		i = -1;
// 		while (++i < e->b.m || e->b.s - i - 1 > e->b.m)
// 			;
// 	}
// 	return (0);
// }

int	print_action(t_ps_env *e, int act)
{
	(void)e;
	(void)act;
	return (0);
}

int	action(t_ps_env *e, int act)
{
	int		t;

	// ft_printf("action: %d\n", act);
	if ((SA & act && e->b.m < 2) || (SB & act && e->b.m > e->b.s - 2) ||
		(PA & act && e->b.m == e->b.s) || (PB & act && e->b.m == 0))
		return (1);
	if (SA & act)
	{
		t = e->b.d[e->b.m - 1];
		e->b.d[e->b.m - 1] = e->b.d[e->b.m - 2];
		e->b.d[e->b.m - 2] = t;
	}
	if (SB & act)
	{
		t = e->b.d[e->b.m];
		e->b.d[e->b.m] = e->b.d[e->b.m + 1];
		e->b.d[e->b.m + 1] = t;
	}
	if (PA & act)
		++e->b.m;
	if (PB & act)
		--e->b.m;
	return (ra_action(e, act) || rb_action(e, act) /*|| print_action(e, act)*/);
}
