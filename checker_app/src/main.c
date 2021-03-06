/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 23:44:11 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 05:48:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>

inline static int	help(char *name)
{
	ft_printf("\nusage: %s [-h --help] [-i --input <path>] [-a --actions <path>"
	"] [-v --verbose] [-c --color] -- int ...\n"
	"-h --help:           show this help\n"
	"-i --input <path>:   specify a file from which to load the A stack\n"
	"-a --actions <path>: specify a file from which to get the actions to apply"
	" to the stacks\n"
	"-v --verbose:        print the stacks at each step\n"
	"-c --color:          color the last actions in the verbose\n", name);
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
		{'a', "actions", 1, 0}, {'c', "color", 0, 0}, {'v', "verbose", 0, 0}};

	ge = ft_getopt_env("hi:a:cv", longopts);
	while ((r = ft_getopt(argc, argv, &ge)) != -1)
		if (r == 'h' || r == 'c')
			e->color = r == 'h' ? help(argv[0]) : 1;
		else if (r == 'v')
			e->verbose = 1;
		else if (r == 'i' && -1 == (e->input = open(ge.optarg, O_RDONLY)))
			exit(0 & ft_printf("can't open file: %s\n", ge.optarg));
		else if (r == 'a' &&
		(e->actions = open(ge.optarg, O_RDONLY)) == -1)
			exit(0 & ft_printf("can't open file: %s\n", ge.optarg));
	if ((r = -1) && !(argc - ge.optind) && e->input == -1)
		exit(0);
	read_args(argc - ge.optind, &argv[ge.optind], e);
}

inline static int	get_code(int fd)
{
	int					i;
	char				*line;
	static const char	*t[17][2] = {{"sa", (char*)SA}, {"sb", (char*)SB},
		{"ss", (char*)SS}, {"ra", (char*)RA}, {"rb", (char*)RB},
		{"rr", (char*)RR}, {"rra", (char*)RRA}, {"rrb", (char*)RRB},
		{"rrr", (char*)RRR}, {"pa", (char*)PA}, {"pb", (char*)PB},
		{"va", (char*)VA}, {"vb", (char*)VB}, {"vv", (char*)VV},
		{"da", (char*)DA}, {"db", (char*)DB}, {"dd", (char*)DD}};

	line = NULL;
	if (get_next_line(fd, &line) > 0)
	{
		i = -1;
		while (++i < 17)
			if (!ft_strcmp((char*)t[i][0], line))
				return ((int)t[i][1]);
	}
	return (0);
}

int					main(int argc, char **argv)
{
	int				act;
	static t_ps_env	env = {.s = {{.first = NULL, .last = NULL, .size = 0,

	.order = 1, .mask = 1 << 7}, {.first = NULL, .last = NULL, .size = 0,
	.order = -1, .mask = 1 << 6}}, .node_head = 0,
	.input = -1, .color = 0, .verbose = 0, .actions = 0};
	ft_error(ERROR_SILENT_ON, NULL);
	read_opts(argc, argv, &env);
	env.s[0].first = env.node_head;
	env.s[0].last = &env.node_head[env.s[0].size - 1];
	if (test_sort(&env))
		exit(_(ft_printf("OK\n"), 0));
	if (env.verbose)
		verbose(&env, VV);
	while ((act = get_code(env.actions)) > 0)
		if (action(&env, act))
			exit(_(ft_printf("KO\n"), 0));
	if (!act)
		ft_printf("Error\n");
	else
		ft_printf("%s\n", test_sort(&env) ? "OK" : "KO");
	free(env.node_head);
}
