/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:34:21 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/17 03:20:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <ft_getopt.h>

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

typedef enum			e_actions
{
	SA  = SWAP | STAC_A,
	SB  = SWAP | STAC_B,
	SS  = SWAP | STAC_A | STAC_B,
	RA  = ROTATE | STAC_A,
	RB  = ROTATE | STAC_B,
	RR  = ROTATE | STAC_A | STAC_B,
	RRA = RROTATE | STAC_A,
	RRB = RROTATE | STAC_B,
	RRR = RROTATE | STAC_A | STAC_B,
	PA  = PUSH | STAC_A,
	PB  = PUSH | STAC_B,
	VA  = VERBOSE | STAC_A,
	VB  = VERBOSE | STAC_B,
	VV  = VERBOSE | STAC_A | STAC_B,
	DA  = DELTA | STAC_A,
	DB  = DELTA | STAC_B,
	DD  = DELTA | STAC_A | STAC_B
}						t_actions;

typedef struct			s_act_list
{
	t_actions			code;
	struct s_act_list	*next;
}						t_act_list;

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

int						recursion(t_ps_env *env, t_pss *stack, size_t size);
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
