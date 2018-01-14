/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 06:01:14 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/14 17:30:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <libftx.h>
# include <ft_getopt.h>

typedef struct			s_bistack
{
	int					*d;
	size_t				s;
	size_t				m;
}						t_bistack;

typedef struct			s_ps_env
{
	t_bistack			b;
	int					opt;
	int					fd;
}						t_ps_env;

# define SA				1
# define SB				2
# define SS				3
# define RA				4
# define RB				8
# define RR				12
# define RRA			16
# define RRB			32
# define RRR			48
# define PA				64
# define PB				128

/*
** additional actions for debbuging purpose
** VA VB VV: same as -v, show the content of piles
** DA DB DD: show where each number should be (in delta places)
*/

# define VA				256
# define VB				512
# define VV				768
# define DA				1024
# define DB				2048
# define DD				3072

# define SCOLOR			"\e[1m\e[30m\e103m"
# define RCOLOR			"\e[1m\e[30m\e102m"
# define RRCOLOR		"\e[1m\e[30m\e101m"
# define PCOLOR			"\e[1m\e[30m\e106m"

# define ACOLOR			"\e[38;5;208m"
# define BCOLOR			"\e[38;5;69"

# define ECOLOR			"\e[91m"
# define KCOLOR			"\e[91m"
# define OCOLOR			"\e[92m"

# define RSCOLOR		"\e[39m"

# define VERBOSE		1
# define COLOR			2
# define GRAPHICAL		4

int						action(t_ps_env *s, int act);
int						print(t_bistack *s);
int						test_full_sort(t_bistack *s);
t_ps_env				*env(void);

int						print_action(t_ps_env *e, int act);

#endif
