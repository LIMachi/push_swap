/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:40:51 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 19:33:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

inline static int	help(char *name)
{
	ft_printf("\nusage: %s [-h --help] [-i --input <path>] [-o"
	" --output <path>] [-n --no-opt] int ...\n-h --help:          show "
	"this help\n-i --input <path>:  specify a file to be used as argume"
	"nt\n-o --output <path>: specify a file to write the instructions\n"
	"-n --no-opt:        do not optimize the quicksort algorithm\n", name);
	exit(0);
	return (0);
}

inline static void	get_args(int argc, char **argv, t_ps_env *e)
{
	t_getopt_env		ge;
	int					r;
	const t_getopt_opt	longopts[] = {{'h', "help", 0, 0}, {'i', "input", 1, 0},
								{'o', "output", 1, 0}, {'n', "no-opt", 0, 0}};

	ge = ft_getopt_env("hi:o:n", longopts);
	while ((r = ft_getopt(argc, argv, &ge)) != -1)
		if (r == 'h' || r == 'n')
			e->no_opt = r == 'h' ? help(argv[0]) : 1;
		else if (r == 'i' && (e->input = open(ge.optarg, O_RDONLY)) == -1)
			exit(0 & ft_printf("can't open file: %s", ge.optarg));
		else if (r == 'o' &&
		(e->input = open(ge.optarg, O_WRONLY | O_CREAT | O_TRUNC)) == -1)
			exit(0 & ft_printf("can't open file: %s", ge.optarg));
	if ((r = -1) && !(argc - ge.optind))
		exit(ft_printf("\n") & 0);
	e->s[0].size = argc - ge.optind;
	if ((e->node_head = malloc(sizeof(t_pss_node) * e->s[0].size)) == NULL)
		exit(0 & ft_printf("failled to alocate the stack\n"));
	while (ge.optind < argc && ++r < argc)
	{
		printf("%p\n", &e->node_head[r]);
		if (!ft_eval_int_ll((e->node_head[r] = (t_pss_node){.value = ft_strtoll(
				argv[ge.optind++], &ge.nextchar, 10), .prev = (r ? &e->node_head[r - 1]
				: NULL), .next = (((size_t)r + 1) < e->s[0].size ? &e->node_head[r + 1] :
				NULL)}).value) || *ge.nextchar)
			exit(_(ft_printf("Error\n"), 2));
	}
}

int					main(int argc, char **argv)
{
	t_act_list		*tmp;
	static t_ps_env	env = {.s = {
		{.first = NULL, .last = NULL, .size = 0, .order = 1, .mask = 1 << 7},
		{.first = NULL, .last = NULL, .size = 0, .order = -1, .mask = 1 << 6}},
		.node_head = 0, .tmp_sort = 0, .input = -1, .output = 1, .no_opt = 0};

	get_args(argc, argv, &env);
	printf("size: %zu\n", env.s[0].size);
	test_duplicates(&env);
	env.s[0].first = env.node_head;
	env.s[0].last = &env.node_head[env.s[0].size - 1];
	printf("ayaye captain\n");
	if ((env.tmp_sort = malloc(sizeof(int64_t) * env.s[0].size)) == NULL)
		exit(0 & ft_printf("failled to alocate the temporary array"));
	while (1);
	quickersort(&env);
	if (env.acts)
	{
		ft_printf("prout\n");
		printer(env.acts, env.output);
	}
	else
		write(env.output, "\n", 1);
	free(env.node_head);
	free(env.tmp_sort);
	while (env.acts)
	{
		tmp = env.acts->next;
		free(env.acts);
		env.acts = tmp;
	}
}
