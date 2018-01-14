/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 05:37:08 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/14 17:33:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static int		h(char *name)
{
	ft_printf("\nusage: %s [-h help] [-v verbose] [-c color] [-g graphic] [-f f"
		"ile <filepath>]\n\n-h help:              show this help\n-f file <file"
		"path>:   file to be used as i/o\n-v verbose [mode]:    print the statu"
		"s of the piles after each step\n-c color:             color the action"
		"s in piles\n-g graphic:           use a graphical representation of th"
		"e stacks\n", name);
	exit(0);
	return (0);
}

static void		get_args(int argc, char **argv)
{
	t_getopt_env		ge;
	int					r;
	const t_getopt_opt	longopts[] = {{'h', "help", 0, 0}, {'c', "color", 0, 0},
		{'v', "verbose", 2, NULL}, {'f', "file", 1, NULL}, {0, NULL, 0, NULL},
		{'g', "graphic", 0, NULL}};

	ge = ft_getopt_env("hv::f:cg", longopts);
	while ((r = ft_getopt(argc, argv, &ge)) != -1)
		if (r == 'c' || r == 'v' || r == 'h')
			(r == 'h' && h(argv[0])) ||
				(env()->opt |= r == 'c' ? COLOR : VERBOSE);
		else if (r == 'g')
			env()->opt |= GRAPHICAL;
		else if (r == 'f')
			if ((env()->fd = open(ge.optarg, O_RDONLY)) == -1)
				exit(_(ft_printf("can't open file: '%s'\n", ge.optarg), 0));
	if (!(argc - ge.optind))
		exit(_(ft_printf("\n"), 0));
	env()->b.s = argc - ge.optind;
	if ((env()->b.d = (int*)ft_malloc(sizeof(int) * env()->b.s)) == NULL)
		exit(_(ft_printf("failled to alocate the stack\n"), 0));
	env()->b.m = 0;
	while (ge.optind < argc)
		if (!ft_eval_int_ll(env()->b.d[env()->b.m++] =
			ft_strtoll(argv[ge.optind++], &ge.nextchar, 10)) || *ge.nextchar)
			exit(_(ft_printf("Error\n"), 0));
}

static int		get_code(int fd)
{
	static const char	*t[17][2] = {{"sa", (char*)SA}, {"sb", (char*)SB},
		{"ss", (char*)SS}, {"ra", (char*)RA}, {"rb", (char*)RB},
		{"rr", (char*)RR}, {"rra", (char*)RRA}, {"rrb", (char*)RRB},
		{"rrr", (char*)RRR}, {"pa", (char*)PA}, {"pb", (char*)PB},
		{"va", (char*)VA}, {"vb", (char*)VB}, {"vv", (char*)VV},
		{"da", (char*)DA}, {"db", (char*)DB}, {"dd", (char*)DD}};
	char				buff[5];
	int					i;
	int					l;

	if ((l = read(fd, buff, 3)) != 3)
		return (l == 0 ? 0 : -1);
	if (buff[2] == 'r' && (l += read(fd, &buff[2], 1) < 2))
		return (-1);
	if (buff[--l] == '\n' || buff[l] == '\0')
		buff[l] = '\0';
	i = -1;
	while (++i < 11)
		if (!ft_strncmp((char*)t[i][0], buff, l))
			return ((int)(size_t)t[i][1]);
	return (-1);
}

static int		action_cycle(t_ftx_data *data)
{
	int c;

	if ((c = get_code(env()->fd)) > 0)
	{
		action(env(), c);
		if (data)
			print_action(env(), c);
		return (c);
	}
	if (!c)
		return (0);
	ft_printf("Error\n");
	while (read(env()->fd, &c, sizeof(int)) > 0)
		;
	exit(0);
	return (0);
}

int				main(int argc, char **argv, char **menv)
{
	t_window		*win;

	ft_env_init(menv);
	get_args(argc, argv);
	if (env()->opt & GRAPHICAL)
	{
		if ((win = ftx_new_window(ft_point(1920, 1080), "checker",
									(const uint64_t *)"checker")) == NULL)
			return (0);
		ftx_loop_hook(action_cycle);
		ftx_start();
	}
	else
		while (action_cycle(NULL))
			;
	ft_putstr(test_full_sort(&env()->b) ? "OK\n" : "KO\n");
	return (0);
}
