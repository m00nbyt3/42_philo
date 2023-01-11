/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2023/01/11 15:21:11 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lunchtime(t_philos *philo, t_iforks *iforks);
int	getfork(t_philos *philo, t_iforks *iforks, int *total);
int	eatnow(t_philos *philo);

int	lunchtime(t_philos *philo, t_iforks *iforks)
{
	int	total;
	int	res;

	if (philo->shared->finish)
		return (1);
	total = 0;
	res = 0;
	while (total != 2)
	{
		usleep(10);
		res = getfork(philo, iforks, &total);
		if (res == 1)
			return (1);
		if (res == 2)
			break ;
	}
	return (0);
}

int	getfork(t_philos *philo, t_iforks *iforks, int *total)
{
	int	fork;

	if (philo->shared->forks[iforks->left] == 1)
		fork = iforks->left;
	if (philo->shared->forks[iforks->right] == 1)
		fork = iforks->right;
	pthread_mutex_lock(&philo->shared->mtx[fork]);
	sprint(philo, PTFORK);
	philo->shared->forks[fork] = 0;
	(*total)++;
	pthread_mutex_unlock(&philo->shared->mtx[fork]);
	if (*total == 2)
	{
		if (eatnow(philo))
			return (1);
		philo->shared->forks[iforks->left] = 1;
		philo->shared->forks[iforks->right] = 1;
		return (2);
	}
	return (0);
}

int	eatnow(t_philos *philo)
{
	sprint(philo, PEAT);
	philo->lasteat = (philo->shared->ctime.tv_sec * 1000) \
	+ (philo->shared->ctime.tv_usec / 1000);
	if (nap(philo->shared->tteat, &philo->shared->finish, philo->shared->pnum))
		return (1);
	if (philo->teaten > 0)
		philo->teaten--;
	return (0);
}
