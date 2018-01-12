/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 07:03:14 by hmartzol          #+#    #+#             */
/*   Updated: 2017/11/24 00:36:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** bistack representation: ('b^a' represent the separation between the two
** stacks, b is read from right to left and a from left to right)
** heuristic: from left to right, find swapable, swap'em, that's all (bubble)
** -----------------------------------------------------------------------------
** bi stack bubble sort (11):
**   1 2 3 6 5 4 7 8 9
** b^a
**   pb pb pb
**   1 2 3 6 5 4 7 8 9
**       b^a
**   sa
**   1 2 3 5 6 4 7 8 9
**       b^a
**   pb sa
**   1 2 3 5 4 6 7 8 9
**         b^a
**   pa sa
**   1 2 3 4 5 6 7 8 9
**       b^a
**   pa pa pa
**   1 2 3 4 5 6 7 8 9
** b^a
** -----------------------------------------------------------------------------
** mono stack bubble sort (replace pb by sa and pa by ssa) (11):
**   1 2 3 6 5 4 7 8 9
**   ra ra ra
**   6 5 4 7 8 9 1 2 3
**   sa
**   5 6 4 7 8 9 1 2 3
**   ra sa
**   4 6 7 8 9 1 2 3 5
**   rra sa
**   4 5 6 7 8 9 1 2 3
**   rra rra rra
**   1 2 3 4 5 6 7 8 9
** -----------------------------------------------------------------------------
** mixed (12):
**   1 2 3 6 5 4 7 8 9
** b^a
**   ra ra ra
**   6 5 4 7 8 9 1 2 3
** b^a
**   pb
**   6 5 4 7 8 9 1 2 3
**   b^a
**   sa
**   6 4 5 7 8 9 1 2 3
**   b^a
**   ra ra pa
**   6 7 8 9 1 2 3 4 5
** b^a
**   ra ra ra ra
**   1 2 3 4 5 6 7 8 9
** b^a
** -----------------------------------------------------------------------------
** heuristic for reverse list (insertion) (worst case scenario, aprox 3*n - 5)
**   9 8 7 6 5 4 3 2 1
** b^a
** (rra pb) * 7 + rra
**   1 2 3 4 5 6 7 8 9
**               b^a
** pa * 7
**   1 2 3 4 5 6 7 8 9
** b^a
** -----------------------------------------------------------------------------
** radix sort
** -----------------------------------------------------------------------------
** delta sort
*/

int	*bubble_sort(t_bistack *s)
{
	(void)s;
	return (0);
}

int	*mono_bubble_sort(t_bistack *s)
{
	(void)s;
	return (0);
}

int	*radix_sort(t_bistack *s)
{
	(void)s;
	return (0);
}

int	*insertion_sort(t_bistack *s)
{
	(void)s;
	return (0);
}

int	*delta_sort(t_bistack *s)
{
	(void)s;
	return (0);
}
