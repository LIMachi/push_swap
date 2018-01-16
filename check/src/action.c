/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 06:00:40 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/14 18:22:02 by hmartzol         ###   ########.fr       */
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

int	action(t_ps_env *e, int act)
{
	int		t;

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
	return (ra_action(e, act) || rb_action(e, act));
}

int	action_cycle(t_ftx_data *data)
{
	int c;

	if ((c = get_code(env()->fd)) > 0)
	{
		action(env(), c);
		if (data)
			print_action(env(), c);
		return (c);
	}
	if (!c)
	{
		ft_end(0);
		return (0);
	}
	ft_printf("Error\n");
	while (read(env()->fd, &c, sizeof(int)) > 0)
		;
	EXIT(0);
	return (0);
}
