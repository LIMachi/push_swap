/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 06:01:14 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 01:14:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <ft_getopt.h>

typedef enum			e_actions
{
	SA  = 0b10000001,
	SB  = 0b01000001,
	SS  = 0b11000001,
	RA  = 0b10000010,
	RB  = 0b01000010,
	RR  = 0b11000010,
	RRA = 0b10000100,
	RRB = 0b01000100,
	RRR = 0b11000100,
	PA  = 0b10001000,
	PB  = 0b01001000,
	VA  = 0b10010000,
	VB  = 0b01010000,
	VV  = 0b11010000,
	DA  = 0b10100000,
	DB  = 0b01100000,
	DD  = 0b11100000
}						t_actions;

typedef struct			s_act_list
{
	t_actions			code;
	s_act_list			*next;
}						t_act_list;

typedef enum			e_actmask
{
	SWAP = 1,
	ROTATE = 2,
	RROTATE = 4,
	PUSH = 8,
	VERBOSE = 16,
	DELTA = 32,
	STAC_A = 64,
	STAC_B = 128
}						t_actmask;

typedef struct			s_pss_node
{
	int64_t				value;
	struct s_pss_node	*prev;
	struct s_pss_node	*next;
}						t_pss_node;

typedef struct			s_pss
{
	t_pss_node			*first;
	t_pss_node			*last;
	size_t				size;
	int64_t				order; //-1 or 1
	t_actmask			mask;
}						t_pss;

# define	SIS 7
# define	BO  -1

typedef struct			s_ps_env
{
	t_pss				s[2];
	int					*tmp_sort; //taille = nombre d'elements, utilisée pour les appels a quicksort
	t_act_list			*acts;
	int					opt;
	int					fd;
}						t_ps_env;

// typedef struct			s_bistack
// {
// 	int					*d;
// 	size_t				s;
// 	size_t				m;
// }						t_bistack;
//
// typedef struct			s_ps_env
// {
// 	t_bistack			b;
// 	int					opt;
// 	int					fd;
// 	t_window			*win;
// }						t_ps_env;

// # define SA				1
// # define SB				2
// # define SS				3
// # define RA				4
// # define RB				8
// # define RR				12
// # define RRA			16
// # define RRB			32
// # define RRR			48
// # define PA				64
// # define PB				128

/*
** additional actions for debbuging purpose
** VA VB VV: same as -v, show the content of piles
** DA DB DD: show where each number should be (in delta places)
*/

// # define VA				256
// # define VB				512
// # define VV				768
// # define DA				1024
// # define DB				2048
// # define DD				3072

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
// int						print(t_bistack *s);
// int						test_full_sort(t_bistack *s);
t_ps_env				*env(void);

int						print_action(t_ps_env *e, int act);
// int						action_cycle(t_ftx_data *data);

int						get_code(int fd);

int						recursion(t_ps_env *env, t_pss *stack);

#endif
