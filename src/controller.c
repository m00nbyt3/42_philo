/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/17 15:09:30 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timepassed(t_philos *philos);

void	timepassed(t_philos *philos)
{
	int	i;
	long	actual;

	while (1)
	{
		i = 0;		
		while (i < philos[0].shared->pnum)
		{
			gettimeofday(&(philos[0].shared->ctime), NULL);
			actual = (philos[0].shared->ctime.tv_sec * 1000000) + philos[0].shared->ctime.tv_usec;
			actual -= philos[i].lasteat;
			if (actual >= philos[i].shared->ttdie)
			{
				philos[i].shared->finish = 1;
				sprint(&philos[0], PDIE);
				return ;
			}
			if (!philos[i].teaten)
				return ;
			i++;
		}
	}
}
