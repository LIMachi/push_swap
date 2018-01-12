/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 06:02:38 by hmartzol          #+#    #+#             */
/*   Updated: 2017/10/16 06:41:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	print(t_bistack *s)
{
	int	i;

	i = s->m;
	ft_putstr("a:\n");
	while (--i >= 0)
	{
		ft_putnbr((int)s->d[i]);
		ft_putchar('\n');
	}
	ft_putstr("b:\n");
	i = s->m - 1;
	while (++i < (int)s->s)
	{
		ft_putnbr((int)s->d[i]);
		ft_putchar('\n');
	}
	return (0);
}
