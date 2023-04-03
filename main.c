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

/*Write an error message and 
exit the program immediately*/
int	ft_err_msg(int msg_id)
{
	if (msg_id == 1)
		write(1, "Error\n", 6);
	if (msg_id == 2)
		write(1, "map error\n", 10);
	return (0);
}

/*Check if any symbols in the grid are not 
the same as either empty or obst. */
int	check_symbols(t_Map *m)
{
	if (m->grid[m->y][m->x] == m->empty)
		return (1);
	if (m->grid[m->y][m->x] == m->obst)
		return (1);
	if (m->grid[m->y][m->x] == '\n')
	return (0);
}

/*Return 0 if any of the symbols in the 
info line are the same as each other. */
int	check_symbols2(t_Map *m)
{
	if (m->empty == m->obst)
		return (0);
	if (m->obst == m->full)
		return (0);
	if (m->empty == m->full)
		return (0);
	return (1);
}

/*Run above two functions, checking for duplicate
symbols and invalid characters on the map itself. 
Also exit if no empty characters are found*/
int	validate(t_Map *m)
{
	int	no_empty;

	no_empty = 1;
	if (check_symbols2(m) != 1)
		return (ft_err_msg(2));
	m->y = 0;
	while (m->y < m->height)
	{
		m->x = 0;
		while (m->x < m->width)
		{
			if (check_symbols(m) == 0)
				return (ft_err_msg(2));
			if (m->grid[m->y][m->x] == m->empty)
				no_empty = 0;
			m->x++;
		}
		m->y++;	
	}
	if (no_empty)
		return (ft_err_msg(2));
	return (1);
}	

int	main(int argc, char **argv)
{
	t_Map	map;
	int		i;
	char	buffer;

	/*if (argc == 1)
	{
		write(1, "Enter the filename for Map\n", 28);
		while(read(0, buffer, 1))
		{
			
			ft_err_msg(1);
		}
	}
	else*/
	i = 1;
	{
		while (i < argc)
		{
			init_memory(&map);
			map.std_in = malloc(sizeof(char) * 50);
			if (map_to_grid(&map, argv[i]))
			{
				map_to_grid(&map, argv[i]);
				if (validate(&map))
				{
					validate(&map);
					solve(&map);
					print_solution(&map);
				}
			}
			free_memory(&map);
			i++;
		}
	}
	return (0);
}
