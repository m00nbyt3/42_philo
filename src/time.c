/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:00:08 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/17 14:37:53 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nap(long msecs, int *imdead)
{
	struct timeval	ctime;
	long			orig;
	long			new;

	gettimeofday(&ctime, NULL);
	orig = (ctime.tv_sec * 1000000) + ctime.tv_usec;
	new = orig + (msecs * 1000);
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
