/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2022/12/13 14:49:56 by ycarro           ###   ########.fr       */
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
			actual = (philos[0].shared->ctime.tv_sec * 1000) + (philos[0].shared->ctime.tv_usec / 1000);
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
