/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:51:33 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 02:31:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** expect argc and argv to have been stripped of any option
*/

/*
** test for duplicates and if there is, free the data and exit
*/

inline static int	test_duplicates(int verbose, t_pss_node *data, size_t size)
{
	size_t	i;
	size_t	j;

	if (size < 2)
		return (0);
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
				if (verbose)
					ft_dprintf(2, "[duplicates]: found two or more iterations o"
						"f %lld\n", data[i].value);
				free(data);
				ft_printf("Error\n");
				exit(2);
			}
		}
	}
	return (0);
}

/*
** the first past detect invalid value (non numeric or non int)
*/

inline static int	first_pass(int argc, char **argv, int verbose)
{
	size_t	size;
	int		i;
	char	*p;
	char	*t;
	int64_t	tmp;

	i = -1;
	size = 0;
	while (++i < argc)
	{
		p = argv[i];
		while (*p)
		{
			if (!ft_eval_int_ll(tmp = ft_strtoll(p, &t, 10)) || p == t ||
					(*t && !ft_isspace(*t)))
				exit(_(verbose ? ft_dprintf(2, "[loader]: %lld is not an int"
					"\n", tmp) : 0, ft_printf("Error\n"), 1));
			_(++size, p = t);
			while (ft_isspace(*p))
				++p;
		}
	}
	if (size < 2)
		exit(0);
	return (size);
}

/*
** alternative loader for the option -i
*/

inline static char	*load_from_file_first_pass(t_ps_env *env)
{
	char	*file;
	char	*p;
	char	*t;
	int64_t	tmp;

	env->s->size = 0;
	if ((file = ft_readfile(env->input)) == NULL)
	{
		if (env->verbose)
			ft_dprintf(2, "[loader]: can't read input file\n");
		exit(3);
	}
	p = file;
	while (*p)
	{
		if (!ft_eval_int_ll(tmp = ft_strtoll(p, &t, 10)) || p == t ||
				(*t && !ft_isspace(*t)))
			exit(_(ft_free(file), env->verbose ? ft_dprintf(2, "[loader]"
				": %lld is not an int\n", tmp) : 0, ft_printf("Error\n"), 1));
		_(++env->s->size, p = t);
		while (ft_isspace(*p))
			++p;
	}
	return (env->s->size < 2 ? _(ft_free(file), NULL) : file);
}

inline static int	load_from_file(t_ps_env *env)
{
	char	*p;
	char	*file;
	size_t	n;

	if ((file = load_from_file_first_pass(env)) == NULL)
		exit(0);
	p = file;
	if ((env->node_head = malloc(sizeof(t_pss_node) * env->s->size)) == NULL)
		exit(0 & ft_printf("failed to allocate the stack\n"));
	n = -1;
	while (*p && ++n < env->s->size)
	{
		while (ft_isspace(*p))
			++p;
		env->node_head[n] = (t_pss_node){.value = ft_strtoll(p, &p, 10),
			.prev = n ? &env->node_head[n - 1] : NULL,
			.next = n + 1 < env->s->size ? &env->node_head[n + 1] : NULL};
	}
	ft_free(file);
	return (test_duplicates(env->verbose, env->node_head, env->s->size));
}

/*
** the second (main) pass allocates, populates, and call test_duplicates
*/

int					read_args(int argc, char **argv, t_ps_env *e)
{
	int		i;
	size_t	n;
	char	*p;

	if (e->input != -1)
		return (load_from_file(e));
	if ((e->s->size = first_pass(argc, argv, e->verbose)) < 2)
		exit(0);
	if ((e->node_head = malloc(sizeof(t_pss_node) * e->s->size)) == NULL)
		exit(0 & ft_printf("failed to allocate the stack\n"));
	i = -1;
	n = -1;
	while (++i < argc)
	{
		p = argv[i];
		while (*p && ++n < e->s->size)
		{
			e->node_head[n] = (t_pss_node){.value = ft_strtoll(p, &p, 10),
				.prev = n ? &e->node_head[n - 1] : NULL,
				.next = n + 1 < e->s->size ? &e->node_head[n + 1] : NULL};
			while (ft_isspace(*p))
				++p;
		}
	}
	return (test_duplicates(e->verbose, e->node_head, e->s->size));
}
