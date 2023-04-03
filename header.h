/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-lima <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:56:08 by bde-lima          #+#    #+#             */
/*   Updated: 2023/03/23 17:58:55 by csharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HEADER_H
# define HEADER_H

typedef struct t_Map
{
	char	*path;
	char	*line;
	char	*std_in;
	char	**grid;
	char	empty;
	char	obst;
	char	full;
	int		solution[3];
	int		height;
	int		width;
	int		info_line;
	int		fd;
//	int		linenb;
//	int		i;
//	int		j;
	int		x;
	int		y;
	int		max_x;
	int		max_y;
}	t_Map;

void	print_solution(t_Map *m);

void	init_memory(t_Map *map);

void	free_memory(t_Map *map);

int		ft_err_msg(int msg_id);

//void	print_grid(t_Map *m);

void	create_grid(t_Map *m);

void	fill_grid(t_Map *m);

//int		solution_check(t_Map m, int i, int j);

int		is_num(char c);

int		ft_atoi(char *num, int size);

//t_Map	validate_map(t_Map p);

int		map_to_grid(t_Map *map, char *path);

void	solve(t_Map *m);

#endif
