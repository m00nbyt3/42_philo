/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:00:08 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/10 14:48:05 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	nap(int secs)
{
	struct timeval	ctime;
	long			orig;
	long			new;

	gettimeofday(&ctime, NULL);
	orig = (ctime.tv_sec * 1000000) + ctime.tv_usec;
	new = orig + (secs * 1000000);
	usleep(secs * 1000000);
	while (orig < new)
	{
		gettimeofday(&ctime, NULL);
		orig = (ctime.tv_sec * 1000000) + ctime.tv_usec;
	}
}
