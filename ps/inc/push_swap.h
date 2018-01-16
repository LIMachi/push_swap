/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:34:21 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/16 19:26:14 by hmartzol         ###   ########.fr       */
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
	struct s_act_list	*next;
}						t_act_list;

typedef enum			e_actmask
{
	SWAP = 1,
	ROTATE = 2,
	RROTATE = 4,
	PUSH = 8,
	VERBOSE = 16,
	DELTA = 32,
	STAC_B = 64,
	STAC_A = 128
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
	int64_t				order;
	t_actmask			mask;
}						t_pss;

typedef struct			s_ps_env
{
	t_pss				s[2];
	t_pss_node			*node_head;
	int64_t				*tmp_sort;
	t_act_list			*acts;
	int					output;
	int					input;
	int					no_opt;
}						t_ps_env;



/*
** src/actions.c
*/

int						action(t_ps_env *e, t_actions act);

/*
** src/micro_sort.c
*/

void					micro_sort(t_ps_env *env);

/*
** src/mini_sort.c
*/

int						mini_sort(t_ps_env *env, t_pss *stack);

/*
** src/optimizer.c
*/

void					optimizer(t_act_list *acts);

/*
** src/printer.c
*/

void					printer(t_act_list *acts, int fd);

/*
** src/queue_action.c
*/

void					queue_action(t_ps_env *e, t_actions act);

/*
** src/quickersort.c
*/

int						recursion(t_ps_env *env, t_pss *stack);
int						quickersort(t_ps_env *env);

/*
** src/test_duplicates.c
*/

void					test_duplicates(t_ps_env *env);

/*
** src/test_sort.c
*/

int						test_sort(t_ps_env *env);

#endif
