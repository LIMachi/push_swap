/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 23:42:11 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/21 01:20:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

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
	VA = VERBOSE | STAC_A,
	VB = VERBOSE | STAC_B,
	VV = VERBOSE | STAC_A | STAC_B,
	DA = DELTA | STAC_A,
	DB = DELTA | STAC_B,
	DD = DELTA | STAC_A | STAC_B
}						t_actions;

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
	int					input;
	int					actions;
	int					verbose;
	int					color;
}						t_ps_env;

/*
** src/actions.c
*/

void					action(t_ps_env *e, t_actions act);

/*
** src/read_args.c
*/

int						read_args(int argc, char **argv, t_ps_env *e);

/*
** src/test_sort.c
*/

int						test_sort(t_ps_env *env);

#endif
