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

/*Find length of info line and length of first map line (width)*/
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

	digits = 0;
	i = 0;
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
	int		curr_width;
	char	buffer;

	m->y = 0;
	curr_width = 0;
	fd = open(m->path, O_RDONLY);
	while (read(fd, &buffer, 1))
	{
		if (m->y != 0)
			curr_width++;
		if (buffer == '\n')
		{
			if ((m->y != 0) && (curr_width != m->width + 1))
				ft_err_msg(2);
			curr_width = 0;
			m->y++;
		}
	}
	if (m->y != (m->height + 1))
		ft_err_msg(2);
	close(fd);
}

void	map_to_grid(t_Map *map, char *path)
{
	first_two_lines(map, path);
	read_info_line(map);
	verify_map_size(map);
	create_grid(map);
	fill_grid(map);
	return ;
}
/*
int	main(void)
{
	t_Map	map;

	map_to_grid(&map, "mapfile");
	print_grid(&map);
	
//	printf("Empty = %c\n", map.empty);
//	printf("Obst = %c\n", map.obst);
//	printf("Full = %c\n", map.full);
//	solve(&map);

//	print_solution(map);
	free(map.grid);
	return (0);
}*/