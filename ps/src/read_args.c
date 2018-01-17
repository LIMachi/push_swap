/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:51:33 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/18 00:44:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** expect argc and argv to have been stripped of any option
*/

/*
** the first past detect invalid value (non numeric or non int)
*/

inline static int	first_pass(int argc, char **argv)
{
	size_t	size;
	int64_t	tmp;
	int		i;
	char	*p;
	char	*t;

	i = -1;
	size = 0;
	while (++i < argc)
	{
		p = argv[i];
		while (*p)
		{
			while (ft_isspace(*p))
				++p;
			if (!ft_eval_int_ll(tmp = ft_strtoll(p, &t, 0)) || p == t ||
					(*t && !ft_isspace(*t)))
				exit(_(ft_printf("Error\n"), 1));
			++size;
			p = t;
		}
	}
	if (size < 2)
		exit(0);
	return (size);
}

/*
** test for duplicates and if there is, free the data and exit
*/

inline static void	test_duplicates(t_pss_node *data, size_t size)
{
	size_t	i;
	size_t	j;

	if (size < 2)
		return ;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (j == i)
				continue ;
			if (data[i].value == data[j].value)
			{
				free(data);
				exit(_(ft_printf("Error\n"), 2));
			}
		}
	}
}

/*
** the second (main) pass alocates, populates, and call test_duplicates
*/

void				read_args(int argc, char **argv, t_ps_env *e)
{
	int		i;
	size_t	n;
	char	*p;

	e->s->size = first_pass(argc, argv);
	if ((e->node_head = malloc(sizeof(t_pss_node) * e->s->size)) == NULL)
		exit(0 & ft_printf("failled to alocate the stack\n"));
	i = -1;
	n = 0;
	while (++i < argc)
	{
		p = argv[i];
		while (*p)
		{
			while (ft_isspace(*p))
				++p;
			e->node_head[n] = (t_pss_node){.value = ft_strtoll(p, &p, 0),
				.prev = n ? &e->node_head[n - 1] : NULL,
				.next = n + 1 < e->s->size ? &e->node_head[n + 1] : NULL};
			++n;
		}
	}
	test_duplicates(e->node_head, e->s->size);
}
