/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 18:21:49 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/14 19:11:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	print_number()

int		print_action(t_ps_env *e, int act)
{
	t_image		*img;
	size_t		i;
	long long	t;
	int			c;
	int			rgb;

	(void)act;
	img = e->win->vbuffer;
	ftx_fill_image(img, 0x33AACC, 1.0);
	i = -1;
	while (++i < e->b.s - e->b.m || i < e->b.m - 1)
	{
		if (i < e->b.s - e->b.m)
		{
			t = e->b.d[e->b.m + i];
			t = t < 0 ? -t : t;
			c = ((double)e->win->size.x / 4.0) * 3.0;
			rgb = e->b.d[e->b.m + i] < 0 ? 0xFF0000 : 0x0000FF;
			ftx_horizontal_line(img, ft_point(e->win->size.x - c - t,
				e->win->size.y - i - 1), ft_point(e->win->size.x - c + t, 0),
				ft_point(rgb, rgb));
		}
		if (i < e->b.m - 1)
		{
			t = e->b.d[i];
			t = t < 0 ? -t : t;
			c = e->win->size.x / 4;
			rgb = e->b.d[i] < 0 ? 0xFF0000 : 0x0000FF;
			ftx_horizontal_line(img, ft_point(e->win->size.x - c - t,
				e->win->size.y - i - 1), ft_point(e->win->size.x - c + t, 0),
				ft_point(rgb, rgb));
		}
	}
	return (0);
}
