/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_duplicates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:21:57 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 19:10:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** test if there is two occurences of the same number in the initial list
*/

void	test_duplicates(t_ps_env *env)
{
	size_t	i;
	size_t	j;

	if (env->s[0].size < 2)
		return ;
	i = -1;
	while (++i < env->s[0].size)
	{
		j = -1;
		while (++j < env->s[0].size)
		{
			if (j == i)
				continue ;
			if (env->node_head[i].value == env->node_head[j].value)
			{
				ft_printf("Error\n");
				exit(1);
			}
		}
	}
}
