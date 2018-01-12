/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 05:37:08 by hmartzol          #+#    #+#             */
/*   Updated: 2017/12/12 13:37:41 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static int		h(char *name)
{
	ft_printf("\nusage: %s [-h help] [-v verbose] [-c color] ", name);
	ft_printf("[-f file <filepath>]\n\n-h help:              show this help\n");
	ft_printf("-f file <filepath>:   file to be used as i/o\n");
	ft_printf("-v verbose [mode]:    print the status of the piles after each");
	ft_printf(" step\n-c color:             color the actions in piles\n");
	exit(0);
	return (0);
}

static t_ps_env	get_args(int argc, char **argv)
{
	t_ps_env			out;
	t_getopt_env		ge;
	int					r;
	const t_getopt_opt	longopts[] = {{'h', "help", 0, 0}, {'c', "color", 0, 0},
		{'v', "verbose", 2, NULL}, {'f', "file", 1, NULL}, {0, NULL, 0, NULL}};

	out = (t_ps_env){.b = {.s = 0, .d = NULL, .m = 0}, .fd = 0, .opt = 0};
	ge = ft_getopt_env("hv::f:c", longopts);
	while ((r = ft_getopt(argc, argv, &ge)) != -1)
		if (r == 'c' || r == 'v' || r == 'h')
			(r == 'h' && h(argv[0])) || (out.opt |= r == 'c' ? COLOR : VERBOSE);
		else if (r == 'f')
			if ((out.fd = open(ge.optarg, O_RDONLY)) == -1)
				exit(_(ft_printf("can't open file: '%s'\n", ge.optarg), 0));
	if (!(argc - ge.optind))
		exit(_(ft_printf("\n"), 0));
	out.b.s = argc - ge.optind;
	if ((out.b.d = (int*)ft_malloc(sizeof(int) * out.b.s)) == NULL)
		exit(_(ft_printf("failled to alocate the stack\n"), 0));
	out.b.m = 0;
	while (ge.optind < argc)
		if (!ft_eval_int_ll(out.b.d[out.b.m++] = ft_strtoll(argv[ge.optind++],
				&ge.nextchar, 10)) || *ge.nextchar)
			exit(_(ft_printf("Error\n"), 0));
	return (out);
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

int				main(int argc, char **argv)
{
	t_ps_env		env;
	int				c;

	env = get_args(argc, argv);
	c = 0;
	while ((c = get_code(env.fd)) > 0)
		action(&env, c);
	if (c == -1)
	{
		ft_printf("Error\n");
		while (read(env.fd, &c, sizeof(int)) > 0)
			;
		exit(0);
	}
	ft_putstr(test_full_sort(&env.b) ? "OK\n" : "KO\n");
	return (0);
}
