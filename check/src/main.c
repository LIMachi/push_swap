/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 02:37:20 by hmartzol          #+#    #+#             */
/*   Updated: 2017/12/12 13:33:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
#include <stdarg.h>

//clang -Iinc -I../libft/inc src/action.c src/checker.c src/push_swap.c src/test.c src/get_args.c src/verbose.c ../libft/libft.a -o checker && echo "ra\nsa" | ./checker 1 2 3

int				cmp(void *a, void *b)
{
	return ((long long)a - (long long)b);
}

int				equal(void *a, void *b)
{
	return ((long long)a == (long long)b);
}

// 4 2 0 1 3 5
// 4 2 0 |AB| 1 3 5
// 4 0 1 5 |AB| 2 3
// 0 1 2 |AB| 3 4 5
// 5 = 101
// n * ln(n)/ln(2) * 5/4

void	error(int exit_code, char *s, ...)
{
	va_list	va;

	va_start(va, s);
	ft_vdprinf(2, s, va);
	va_end(va);
	exit(exit_code);
}

static t_ps_env	get_args(int argc, char **argv)
{
	t_ps_env			out;
	t_getopt_env		ge;
	int					r;
	const t_getopt_opt	longopts[] = {{'h', "help", 0, 0}, {0, NULL, 0, NULL}};

	out = (t_ps_env){.b = {.s = 0, .d = NULL, .m = 0}, .fd = 0, .opt = 0};
	ge = ft_getopt_env("h", longopts);
	while ((r = ft_getopt_base(argc, argv, &ge)) != -1)
		if (r == 'c' || r == 'v' || r == 'h')
			(r == 'h' && h(argv[0])) || (out.opt |= r == 'c' ? COLOR : VERBOSE);
		else if (r == 'f')
			if ((out.fd = open(ge.optarg, O_RDONLY)) == -1)
				exit(_(ft_printf("can't open file: '%s'\n", ge.optarg), 0));
	if (!(argc - ge.optind))
		error(EXIT_SUCCESS, "\n");
	out.b.s = argc - ge.optind;
	if ((out.b.d = (int*)ft_malloc(sizeof(int) * out.b.s)) == NULL)
		exit(_(ft_printf("failed to allocate the stack\n"), 0));
	out.b.m = 0;
	while (ge.optind < argc)
		if (!ft_eval_int_ll(out.b.d[out.b.m++] = ft_strtoll(argv[ge.optind++],
				&ge.nextchar, 10)) || *ge.nextchar)
			exit(_(ft_printf("Error\n"), 0));
	return (out);
}

int				main(int argc, char **argv)
{
	int				i;
	t_bistack		bstack;
	// char			buff[256];
	// unsigned char	c;
	char			*tc;

	bstack = (t_bistack){
		(int*)malloc(sizeof(int) * (argc - 1)), argc - 1, argc - 1};
	if (bstack.d == NULL)
		return (_(write(1, "Error\n", 6), 0));
	i = argc;
	while (--i)
		if ((bstack.d[argc - i - 1] = (void*)ft_strtoll(argv[i], &tc, 10)), *tc
			|| !(ft_eval_int_ll((unsigned long long)bstack.d[argc - i - 1])))
			return (_(write(1, "Error\n", 6), 0));
	// while ((i = read(0, buff, 255)))
	// {
	// 	buff[i - 1] = '\0';
	// 	if (!(c = get_code(buff)) || action(&bstack, c))
	// 		return (_(write(1, "Error\n", 6), 0));
	// 	print(&bstack);
	// }
	void	**t = ft_memcpy(ft_malloc(8 * argc), bstack.d, (argc - 1) * 8);
	ft_memquicksort(bstack.d, argc - 1, &cmp);
	size_t	*ind = ft_memindexes(bstack.d, t, &equal, argc - 1);
	printf("dbg\n");
	for (int i = 0; i < argc - 1; ++i)
		printf("%zu\n", ind[i]);
	printf("ok\n");
	print(&bstack);
	if (test_full_sort(&bstack))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	return (0);
}
