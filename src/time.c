/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:00:08 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/15 15:33:34 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nap(int secs, int *imdead)
{
	struct timeval	ctime;
	long			orig;
	long			new;

	gettimeofday(&ctime, NULL);
	orig = (ctime.tv_sec * 1000000) + ctime.tv_usec;
	new = orig + (secs * 1000000);
	while (orig < new)
	{
		usleep(10);
		if (*imdead)
			return (1);
		gettimeofday(&ctime, NULL);
		orig = (ctime.tv_sec * 1000000) + ctime.tv_usec;
	}
	return (0);
}
