/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickersort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 04:51:45 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/18 20:37:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** optimized implementation of quicksort using the best median (resulting from
** an actual call to quicksort) and with verfication of usefullness of commands
** ~5000 operation for 500 random elements
** O(n * log2(n)) (real quicksort O(n * log(n)))
*/

/*
** stupidest yet simplest way of getting a median, just sort the local segment
** (after copying it to not mess the original), take the middle element of said
** sort and voila
*/

inline static int	optimum_median(t_pss_node *node, int64_t *tmp_sort,
									size_t size)
{
	size_t	i;

	i = 0;
	while (node && size--)
	{
		tmp_sort[i++] = node->value;
		node = node->next;
	}
	return (ft_quicksort(tmp_sort, i)[i / 2]);
}

/*
** determine if there is still elements in the stack that are lower or bigger
** (based on list order) than the median
*/

inline static int	continue_cycle(t_pss_node *node, int64_t pivot,
									int64_t order, size_t size)
{
	while (node && size--)
	{
		if (node->value * order < pivot)
			return (1);
		node = node->next;
	}
	return (0);
}

/*
** cut the recursion in 2 parts, thanks 42 and your odd norms
*/

inline static void	rec1(t_ps_env *env, t_pss *stack, size_t rotations,
						size_t pushes)
{
	if (stack->mask == STAC_B)
		recursion(env, env->s, pushes);
	if (rotations > stack->size / 2 && stack->size > 3)
		while (rotations++ < stack->size)
			action(env, stack->mask | ROTATE);
	else if (stack->size > 3)
		while (rotations--)
			action(env, stack->mask | RROTATE);
}

/*
** lower/bigger elements than local median get pushed to the other stack
** on back track: unpile all elements pushed
** basic reproduction of a quicsort
*/

int					recursion(t_ps_env *env, t_pss *stack, size_t size)
{
	int64_t	pivot;
	size_t	rotations;
	size_t	pushes;
	size_t	i;

	pushes = 0;
	rotations = 0;
	if (size <= 3)
		return (mini_sort(env, stack));
	pivot = optimum_median(stack->first, env->tmp_sort, size) * stack->order;
	i = 0;
	while (continue_cycle(stack->first, pivot, stack->order, size - i) &&
			i++ < size)
		if (stack->first->value * stack->order < pivot)
			action(env, (stack->mask ^ 0b11000000) | PUSH | (0 & ++pushes));
		else
			action(env, stack->mask | ROTATE | (0 & ++rotations));
	rec1(env, stack, rotations, pushes);
	recursion(env, stack, size - pushes);
	if (stack->mask == STAC_A)
		recursion(env, &env->s[1], pushes);
	while (pushes--)
		action(env, stack->mask | PUSH);
	return (0);
}

/*
** not the actual sort, it just choses the best way of sorting the list,
** initiate the recursion and clean the result
*/

int					quickersort(t_ps_env *env)
{
	if (env->s[0].size > 3)
		recursion(env, env->s, env->s->size);
	else
		micro_sort(env);
	if (!env->no_opt && env->acts)
		env->acts = optimizer(env->acts);
	return (0);
}
