/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:27:07 by hmartzol          #+#    #+#             */
/*   Updated: 2018/01/17 02:06:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** unpile a set of code of instruction and print them in reverse order
** (first element will be print last)
*/

void	printer(t_act_list *acts, int fd)
{
	char	buff[4];
	int		i;

	if (acts->next != NULL)
		printer(acts->next, fd);
	if (!(i = 0) && acts->code & SWAP)
		buff[i++] = 's';
	else if (acts->code & ROTATE)
		buff[i++] = 'r';
	else if (acts->code & PUSH)
		buff[i++] = 'p';
	else if (acts->code & RROTATE)
	{
		buff[i++] = 'r';
		buff[i++] = 'r';
	}
	if ((acts->code & (STAC_A | STAC_B)) == (STAC_A | STAC_B))
		buff[i] = buff[i - 1];
	else if (acts->code & STAC_A)
		buff[i] = 'a';
	else if (acts->code & STAC_B)
		buff[i] = 'b';
	buff[++i] = '\n';
	write(fd, buff, i + 1);
}
