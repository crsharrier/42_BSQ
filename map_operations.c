/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:39:34 by csharrie          #+#    #+#             */
/*   Updated: 2023/03/23 10:46:44 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "header.h"

/*Receive a struct containing a valid height and width.
 *Assign empty grid to m->map_grid. */
void	create_grid(t_Map *m)
{
	//printf("m->height = %i, m->width = %i\n", m->height, m->width);
	m->grid = malloc(sizeof(char*) * (m->height + 1));
	m->grid[m->height] = '\0';
	m->y = 0;
	while (m->y < m->height)
	{
		m->grid[m->y] = malloc(sizeof(char) * (m->width + 1));
		m->grid[m->y][m->width] = '\0';
		m->y++;
	}
}

/*Once empty grid has been created, fill it with appropriate
empty and obst symbols. */
void	fill_grid(t_Map *m)
{
	int fd;
	char	buffer;

	m->x = 0;
	m->y = 0;
	fd = open(m->path, O_RDONLY);
	while (read(fd, &buffer, 1) && (m->y <= m->height))
	{
		if (m->y)
		{
			m->grid[m->y - 1][m->x] = buffer;
			m->x++;
		}
		if (buffer == '\n')
		{
			m->x = 0;
			m->y++;
		}
	}
	close(fd);
}

/*Print input grid. (Mainly for testing purposes)
void	print_grid(t_Map *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (m->grid[i][j])
			write(1, &m->grid[i][j++], 1);
		i++;
	}
}*/

int	solution_check(t_Map *m, int i, int j)
{
	if (i < m->solution[1] || i > (m->solution[1] + m->solution[2]))
		return (0);
	if (j < m->solution[0] || j > (m->solution[0] + m->solution[2]))
		return (0);
	return (1);
}

/*Print SOLUTION grid.*/
void	print_solution(t_Map *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (m->grid[i][j])
		{
			if (solution_check(m, i, j))
				write(1, &m->full, 1);
			else
				write(1, &m->grid[i][j], 1);
			j++;
		}
		j = 0;
		i++;
	}
}
/*
int	main(void)
{
	printf("5 = %i", is_num('5'));
	printf("e = %i", is_num('e'));
	printf("0 = %i", is_num('0'));
	return (0);
}*/
