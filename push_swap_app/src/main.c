/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:40:51 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 04:29:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

inline static int	help(char *name)
{
	ft_printf("\nusage: %s [-h --help] [-i --input <path>] [-o --output <path>]"
	" [-v --verbose] [-n --no-opt] -- int ...\n"
	"-h --help:          show this help\n"
	"-i --input <path>:  specify a file from wich load the A stack\n"
	"-o --output <path>: specify a file to write the instructions\n"
	"-v --verbose:       print additional information on stderror\n"
	"-n --no-opt:        do not optimize the quicksort algorithm\n", name);
	exit(0);
	return (0);
}

/*
** get the options from argv and then call read_args to get the actual stack
*/

inline static void	read_opts(int argc, char **argv, t_ps_env *e)
{
	t_getopt_env		ge;
	size_t				r;
	const t_getopt_opt	longopts[] = {{'h', "help", 0, 0}, {'i', "input", 1, 0},
		{'o', "output", 1, 0}, {'n', "no-opt", 0, 0}, {'v', "verbose", 0, 0}};

	ge = ft_getopt_env("hi:o:nv", longopts);
	while ((r = ft_getopt(argc, argv, &ge)) != -1)
		if (r == 'h' || r == 'n')
			e->no_opt = r == 'h' ? help(argv[0]) : 1;
		else if (r == 'v')
			e->verbose = 1;
		else if (r == 'i' && -1 == (e->input = open(ge.optarg, O_RDONLY)))
			exit(0 & ft_printf("can't open file: %s\n", ge.optarg));
		else if (r == 'o' &&
		(e->output = open(ge.optarg, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			exit(0 & ft_printf("can't open file: %s\n", ge.optarg));
	if ((r = -1) && !(argc - ge.optind) && e->input == -1)
		exit(0);
	read_args(argc - ge.optind, &argv[ge.optind], e);
}

int					main(int argc, char **argv)
{
	t_act_list		*tmp;
	static t_ps_env	env = {.s = {{.first = NULL, .last = NULL, .size = 0,

	.order = 1, .mask = 1 << 7}, {.first = NULL, .last = NULL, .size = 0,
	.order = -1, .mask = 1 << 6}}, .node_head = 0, .tmp_sort = 0, .acts = 0,
	.output = 1, .no_opt = 0, .verbose = 0, .input = -1};
	read_opts(argc, argv, &env);
	env.s[0].first = env.node_head;
	env.s[0].last = &env.node_head[env.s[0].size - 1];
	if ((env.tmp_sort = malloc(sizeof(int64_t) * env.s[0].size)) == NULL)
		exit(0 & ft_printf("failed to allocate the temporary array"));
	quickersort(&env);
	if (env.acts)
		printer(env.acts, env.output);
	free(env.node_head);
	free(env.tmp_sort);
	while (env.acts)
	{
		tmp = env.acts->next;
		free(env.acts);
		env.acts = tmp;
	}
}
