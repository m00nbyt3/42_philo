/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:00:08 by ycarro            #+#    #+#             */
/*   Updated: 2022/01/25 12:58:54 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	nap(int secs)
{

	struct 	timeval ctime;
	long	orig;
	long	new;

	gettimeofday(&ctime, NULL);
	orig = ctime.tv_sec;
	new = orig + secs;
	usleep(secs * 1000000);
	while (orig != new)
	{
		gettimeofday(&ctime, NULL);
		orig = ctime.tv_sec;
	}
}

void	nap_old(int secs)
{
	struct timeval ctime;
	long orig;
	long end;
	long tmp;

	secs--;
	gettimeofday(&ctime, NULL);
	orig = ctime.tv_sec;
	printf("%ld\n", (orig % 10));
	end = orig + 5;
	while (orig != end)
	{	
		tmp = orig;
		gettimeofday(&ctime, NULL);
		orig = ctime.tv_sec;
		if (orig != tmp)
			printf("%ld\n", (orig % 10));
	}
}
