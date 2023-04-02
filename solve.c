/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:08:18 by csharrie          #+#    #+#             */
/*   Updated: 2023/03/22 22:59:50 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/*Take our struct and the current p.x and p.y. Iterate over the area defined 
 *by p.max and return 0 if an obstacle is found. Else return 1.*/
int	no_obstacle(t_Map *m, int i, int j)
{
	while (i <= m->max_y)
	{
		j = m->x;
		while (j <= m->max_x)
		{
			if (m->grid[i][j] != m->empty)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*Check how far diagonally we can find empty characters.
 * Return struct p, having modified p.max_x and p.max_y*/
void	check_diag(t_Map *m)
{
	m->max_x = m->x;
	m->max_y = m->y;
	while (m->max_y < m->height && m->grid[m->max_y][m->max_x] == m->empty)
	{
		m->max_x++;
		m->max_y++;
	}
	m->max_x--;
	m->max_y--;
}

/*Starting at the current p.x, check if a bigger square can be found*/
void	check_square(t_Map *m)
{	
	check_diag(m);
	while (m->max_y >= m->y)
	{
		if (no_obstacle(m, m->y, m->x) == 1)
		{
			if ((m->max_y - m->y) > m->solution[2])
			{
				m->solution[0] = m->x;
				m->solution[1] = m->y;
				m->solution[2] = m->max_x - m->x;
			}
		}
		m->max_x--;
		m->max_y--;
	}
}

/*Take a t_Map struct containing a map in p.map_grid. Store the x and y 
 *index of the start of solution square, and its size in p.solution 
 *(which is of type int[3])*/
void	solve(t_Map *m)
{
	m->solution[2] = 0;
	m->y = 0;
	while (m->y < m->height)
	{
		m->x = 0;
		while (m->grid[m->y][m->x] != 0)
		{
			if (m->grid[m->y][m->x] == m->empty)
				check_square(m);
			m->x++;
		}
		m->y++;
	}
}
/*
int	main(void)
{
	t_Map	map;

	map_to_grid(&map, "mapfile");
//	print_grid(&map);
//	printf("Empty = %c\n", map.empty);
//	printf("Obst = %c\n", map.obst);
//	printf("Full = %c\n", map.full);
	solve(&map);
//	printf("solution[0] = %i\n", map.solution[0]);
//	printf("solution[1] = %i\n", map.solution[1]);
//	printf("solution[2] = %i\n", map.solution[2]);
	print_solution(&map);
	free(map.grid);
	return (0);
}*/
