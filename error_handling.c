/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:08:31 by csharrie          #+#    #+#             */
/*   Updated: 2023/03/23 10:57:29 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"

void	ft_err_msg(int msg_id)
{
	if (msg_id == 1)
		write(1, "Error\n", 6);
	if (msg_id == 2)
		write(1, "map error\n", 10);
	exit(0);
}

int	check_symbols(t_Map p)
{
	if (p.map_str[p.x] == p.empty)
		return (1);
	if (p.map_str[p.x] == p.obst)
		return (1);
	if (p.map_str[p.x] == p.full)
		return (1);
	return (0);
}

int	check_symbols2(t_Map p)
{
	if (is_num(p.map_str[p.x - 2]) == 1)
		return (0);
	if (is_num(p.map_str[p.x - 1]) == 1)
		return (0);
	if (is_num(p.map_str[p.x - 3]) == 1)
		return (0);
	return (1);
}

t_Map	validate_pt2(t_Map p)
{
	int	len;

	while (p.map_str[p.x++] != '\n')
	{
		if (check_symbols(p) == 0)
		{	
			printf("current char = %c", p.map_str[p.x]);
			printf("ERROR1");
			ft_err_msg(2);
		}
		p.y++;
	}
	p.x++;
	len = p.y;
	while (p.height > p.linenb)
	{
		p.y = 0;
		while (p.map_str[p.x++] != '\n')
		{
			if (check_symbols(p) == 0)
			{
				printf("ERROR2");
				ft_err_msg(2);
			}
			p.y++;
		}
		if (len != p.y)
		{
			printf("ERROR3");
			ft_err_msg(2);
		}
		p.linenb++;
	}
	return (p);
}

t_Map	validate_map(t_Map p)
{
	int	i;
	int	len;
	int	width;

	p.x = 0;
	while (p.map_str[p.x] != '\n')
		p.x++;
	if (check_symbols2(p) == 0)
	{
		printf("p.x - 1 = %i\n", is_num(p.map_str[p.x - 1]));
		printf("p.x - 2 = %i\n", is_num(p.map_str[p.x - 2]));
		printf("p.x - 3 = %i\n", is_num(p.map_str[p.x - 3]));
		printf("ERROR4");
		ft_err_msg(2);
	}
	p.height = ft_atoi(p.map_str, p.x - 3);
	p.empty = p.map_str[p.x - 3];
	p.obst = p.map_str[p.x - 2];
	p.full = p.map_str[p.x - 1];
	p.x++;
	if ((p.empty == p.obst) || (p.obst == p.full) || (p.empty == p.full))
	{
		printf("ERROR5");
		ft_err_msg(2);
	}
	p.y = 0;
	p.linenb = 1;
	p = validate_pt2(p);
	return (p);
}	
