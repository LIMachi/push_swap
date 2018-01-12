/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 06:30:52 by hmartzol          #+#    #+#             */
/*   Updated: 2017/10/17 00:31:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdio.h>

int	test_full_sort(t_bistack *s)
{
	int	i;

	if (s->m != s->s)
		return (0);
	i = 0;
	while (++i < (int)s->m)
		if ((int)s->d[i - 1] <= (int)s->d[i])
			return (0);
	return (1);
}
