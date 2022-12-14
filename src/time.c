/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:00:08 by ycarro            #+#    #+#             */
/*   Updated: 2022/12/14 17:08:01 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nap(long msecs, int *imdead, int towait)
{
	struct timeval	ctime;
	long			orig;
	long			new;

	gettimeofday(&ctime, NULL);
	orig = (ctime.tv_sec * 1000) + (ctime.tv_usec / 1000);
	new = orig + msecs;
	while (orig < new)
	{
		usleep(towait);
		if (*imdead)
			return (1);
		gettimeofday(&ctime, NULL);
		orig = (ctime.tv_sec * 1000) + (ctime.tv_usec / 1000);
	}
	return (0);
}

int	s_nap(long msecs)
{
	struct timeval	ctime;
	long			orig;
	long			new;

	gettimeofday(&ctime, NULL);
	orig = (ctime.tv_sec * 1000) + (ctime.tv_usec / 1000);
	new = orig + msecs;
	while (orig < new)
	{
		usleep(5);
		gettimeofday(&ctime, NULL);
		orig = (ctime.tv_sec * 1000) + (ctime.tv_usec / 1000);
	}
	return (0);
}