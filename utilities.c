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

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_power(int nb, int power)
{
	if (power)
		return (nb * ft_power(nb, power - 1));
	return (1);
}

int	ft_atoi(char *num, int size)
{
	int	total;

	total = 0;
	while (*num > '0' && *num < '9')
	{
		total += (*num - 48) * ft_power(10, size - 1);
		num++;
		size--;
	}
	return (total);
}

int	solution_check(t_Map p, int i, int j)
{
	if (j < p.solution[1] || j > (p.solution[1] + p.solution[2]))
		return (0);
	if (i < p.solution[0] || i > (p.solution[0] + p.solution[2]))
		return (0);
	return (1);
}

/*Prints SOLUTION grid. Requires height as parameter!*/
void	print_solution(t_Map p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < p.height)
	{
		while (p.grid[i][j])
		{
			if (solution_check(p, i, j))
				write(1, &p.full, 1);
			else
				write(1, &p.grid[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
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
