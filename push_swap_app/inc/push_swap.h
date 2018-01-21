/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:34:21 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/20 03:19:50 by hmartzol         ###   ########.fr       */
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
	STAC_B = 64,
	STAC_A = 128
}						t_actmask;

typedef enum			e_actions
{

	SB = 65,
	RB = 66,
	RRB = 68,
	PB = 72,
	SA = 129,
	RA = 130,
	RRA = 132,
	PA = 136,
	SS = 193,
	RR = 194,
	RRR = 196,
}						t_actions;

typedef struct			s_act_list
{
	t_actions			code;
	struct s_act_list	*prev;
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
	int					input;
	int					output;
	int					no_opt;
	int					verbose;
}						t_ps_env;

/*
** src/actions.c
*/

void					action(t_ps_env *e, t_actions act);

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

t_act_list				*optimizer(t_act_list *acts, int verbose);

/*
** src/printer.c
*/

void					printer(t_act_list *acts, int fd);
const char				*label(t_actions act);

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
** src/read_args.c
*/

int						read_args(int argc, char **argv, t_ps_env *e);

/*
** src/test_sort.c
*/

int						test_sort(t_ps_env *env);

#endif
