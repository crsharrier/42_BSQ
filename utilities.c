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

void	free_memory(t_Map *map)
{
	if (map->grid)
		free(map->grid);
	if (map->std_in)
		free(map->std_in);
}

/*
int	main(void)
{
	printf("5 = %i", is_num('5'));
	printf("e = %i", is_num('e'));
	printf("0 = %i", is_num('0'));
	return (0);
}*/
