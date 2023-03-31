/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_grid2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:39:34 by csharrie          #+#    #+#             */
/*   Updated: 2023/03/23 18:11:04 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "header.h"

/*Find length of info line and length of first map line*/
void	first_two_lines(t_Map *m, char *path)
{
	char	buffer;
	int		fd;
	int		line;

	m->info_line = 0;
	m->width = 0;
	m->path = path;
	line = 0;
	fd = open(path, O_RDONLY);
	while (read(fd, &buffer, 1) && line < 2)
	{
//		printf("m->info_line = %i, m->width = %i\n", m->info_line, m->width);
		if (buffer == '\n')
			line++;
		else
		{
			if (line == 0)
				m->info_line++;
			else
				m->width++;
		}
	}
	close(fd);
}

/*Read length and full, empty and obst symbols from info line. If info
line is incorrect length, ft_err_msg(2) */
void	read_info_line(t_Map *m)
{
	int		fd;
	int		digits;
	int		i;
	char	buffer;
	char	*line;

	line = malloc(sizeof(char) * m->info_line);
	fd = open(m->path, O_RDONLY);
	while (read(fd, &buffer, 1) && (buffer != '\n'))
	{
		if (is_num(buffer))
			digits++;
		line[i] = buffer;
		i++;
	}
	if (i != (digits + 3))
		ft_err_msg(2);
	m->empty = line[digits];
	m->obst = line[digits + 1];
	m->full = line[digits + 2];
	m->height = ft_atoi(line, digits);
	free(line);
	close(fd);
}

/*Verify that the map is the correct length and width*/
void	verify_map_size(t_Map *m)
{
	int		fd;
	int		line_n;
	int		curr_width;
	char	buffer;

	line_n = 0;
	curr_width = 0;
	fd = open(m->path, O_RDONLY);
	while (read(fd, &buffer, 1))
	{
		write(1, &buffer, 1);
		if (line_n != 0)
			curr_width++;
		if (buffer == '\n')
		{
//			printf("curr_width = %i, m->width = %i\n", curr_width, m->width);
			if ((line_n != 0) && (curr_width != m->width - 1))
				ft_err_msg(2);
			curr_width = 0;
			line_n++;
		}
	}
	if (line_n != (m->height - 1))
		ft_err_msg(2);
	close(fd);
}
/*Receive a struct containing a VALID map_str.
 *Assign height and symbols to p.height, p.empty, p.obst, p.full
 *Assign empty grid to p.map_grid. */
/*t_Map	create_grid(t_Map *p)
{
	int	width;

	p->x = 0;
	while (p->map_str[p->x] != '\n')
		p->x++;
	p->x++;
	p->map_str += p->x;
	width = 1;
	while (p->map_str[p->x++] != '\n')
		width++;
	p->grid = malloc(sizeof(char *) * p->height);
	p->y = 0;
	while (p->y < p->height)
	{
		p->grid[p->y] = malloc(sizeof (char) * (width + 1));
		p->y++;
	}
	return (p);
}
*/
/* Pick up where create_grid left off. Advance map pointer to first 'map' line.
 * Move through grid, assigning values line by line */
t_Map	fill_grid(t_Map p)
{	
	p.x = 0;
	while (*p.map_str)
	{
		p.y = 0;
		while (*p.map_str != '\n' && *p.map_str)
		{
			p.grid[p.x][p.y] = *p.map_str++;
			p.y++;
		}
		p.grid[p.x][p.y] = '\0';
		p.x++;
		p.map_str++;
	}
	return (p);
}

/*Prints grid. Requires height as parameter!*/
void	print_grid(t_Map p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < p.height)
	{
		while (p.grid[i][j])
			write(1, &p.grid[i][j++], 1);
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}
/*
void	map_to_grid(char *path)
{
	return ;
}
*/
int	main(void)
{
	t_Map	map;

	first_two_lines(&map, "mapfile");
	read_info_line(&map);
//	verify_map_size(&map);
	printf("Empty = %c\n", map.empty);
	printf("Obst = %c\n", map.obst);
	printf("Full = %c\n", map.full);
//	solve(map);
//	print_grid(map);
//	print_solution(map);
	return (0);
}
