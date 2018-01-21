/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 05:37:08 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/20 00:25:41 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** verbose, couleur, non-opt sur ps, mode interactif, files, verbose sur optimisation
*/

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

static void		get_args(int argc, char **argv, t_ps_env *e)
{
	t_getopt_env		ge;
	int					r;
	const t_getopt_opt	longopts[] = {{'h', "help", 0, 0}, {'c', "color", 0, 0},
		{'v', "verbose", 2, NULL}, {'f', "file", 1, NULL}, {0, NULL, 0, NULL},
		{'g', "graphic", 0, NULL}};

	ge = ft_getopt_env("hv::f:cg", longopts);
	while ((r = ft_getopt(argc, argv, &ge)) != -1)
		if (r == 'c' || r == 'v' || r == 'h')
			(r == 'h' && h(argv[0])) || (e->opt |= r == 'c' ? COLOR : VERBOSE);
		else if (r == 'g')
			e->opt |= GRAPHICAL;
		else if (r == 'f')
			if ((e->fd = open(ge.optarg, O_RDONLY)) == -1)
				exit(_(ft_printf("can't open file: '%s'\n", ge.optarg), 0));
	if (!(argc - ge.optind))
		exit(_(ft_printf("\n"), 0));
	e->b.s = argc - ge.optind;
	if ((e->b.d = (int*)ft_malloc(sizeof(int) * e->b.s)) == NULL)
		exit(_(ft_printf("failed to allocate the stack\n"), 0));
	e->b.m = 0;
	while (ge.optind < argc)
		if (!ft_eval_int_ll(e->b.d[e->b.m++] =
			ft_strtoll(argv[ge.optind++], &ge.nextchar, 10)) || *ge.nextchar)
			exit(_(ft_printf("Error\n"), 0));
}

int				get_code(int fd)
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

void			closer(void)
{
	ft_putstr(test_full_sort(&env()->b) ? "OK\n" : "KO\n");
}

int				main(int argc, char **argv, char **menv)
{
	int		s;
	size_t	i;

	ft_env_init(menv);
	ft_atend(&closer);
	get_args(argc + (s = 0), argv, env());
	i = -1;
	while (++i < env()->b.s)
		if (env()->b.d[i] < 0)
			s = s > -env()->b.d[i] ? s : -env()->b.d[i];
		else
			s = s > env()->b.d[i] ? s : env()->b.d[i];
	s = s < 200 ? 200 : s;
	if (env()->opt & GRAPHICAL)
	{
		if ((env()->win = ftx_new_window(ft_point(s * 2 + 1, env()->b.s < 100 ?
			100 : env()->b.s), "checker", (const uint64_t *)"checker")) == NULL)
			return (0);
		ftx_loop_hook(action_cycle);
		ftx_start();
	}
	else
		while (action_cycle(NULL))
			;
	return (0);
}
