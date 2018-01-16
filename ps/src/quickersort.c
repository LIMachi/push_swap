/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickersort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 04:51:45 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 01:54:36 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** optimized implementation of quicksort using the best median (resulting from
** an actual call to quicksort) and with verfication of usefullness of commands
** ~5000 operation for 500 random elements
** O(n * log2(n)) (real quicksort O(n * log(n)))
*/

inline static int	optimum_median(t_pss_node *node, int *tmp_sort)
{
	size_t	i;

	i = 0;
	while (node)
	{
		tmp_sort[i++] = node->value;
		node = node->next;
	}
	return (ft_quicksort(tmp_sort, i)[i / 2]);
}

inline static int	continue_cycle(t_pss_node *node, int pivot, int order)
{
	while (node)
	{
		if (node->value * order < pivot)
			return (1);
		node = node->next;
	}
	return (0);
}

inline static int	rec1(t_ps_env *env, t_pss *stack, int rotations, int pushes)
{
	if (stack->mask == STAC_B)
		recursion(env, &env->s[0]);
	if (rotations > stack->size / 2 && stack->size > 3)
		while (rotations++ < stack->size)
			action(env, stack->mask | ROTATE);
	else if (stack->size > 3)
		while (rotations--)
			action(env, stack->mask | RROTATE);
	if (stack->mask == STAC_A)
		recursion(env, stack);
	recursion(env, &env->s[1]);
	while (pushes--)
		action(env, stack->mask | PUSH);
	return (0);
}

int					recursion(t_ps_env *env, t_pss *stack)
{
	int	pivot;
	int	rotations;
	int	pushes;

	pushes = 0;
	rotations = 0;
	if (stack->size <= 3)
		return (mini_sort(env, stack));
	pivot = optimum_median(stack->first, env->tmp_sort);
	while (continue_cycle(stack->first, pivot, stack->order))
		if (stack->first->value * stack->order < pivot)
		{
			++pushes;
			action(env, (stack->mask ^ 0b11000000) | PUSH);
		}
		else
		{
			++rotations;
			action(env, stack->mask | ROTATE);
		}
	return (rec1(env, stack, rotations, pushes));
}

int					quickersort(t_ps_env *env)
{
	if (env->s[0].size > 3)
		recursion(env, env->s);
	else
		micro_sort(env);
	optimizer(env->acts);
	return (0);
}
