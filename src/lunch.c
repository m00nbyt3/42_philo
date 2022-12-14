/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2022/12/14 16:20:32 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lunchtime(t_philos *philo, t_iforks *iforks);
int	eatnow(t_philos *philo);

int	lunchtime(t_philos *philo, t_iforks *iforks)
{
	int	fork1;
	int	fork2;

	if (philo->shared->finish)
			return (1);
	fork1 = iforks->right;
	fork2 = iforks->left;
	if (philo->id % 2)
	{
		fork1 = iforks->left;
		fork2 = iforks->right;
	}
	pthread_mutex_lock(&philo->shared->mtx[fork1]);
	sprint(philo, PTFORK);
	pthread_mutex_lock(&philo->shared->mtx[fork2]);
	sprint(philo, PTFORK);
	sprint(philo, PEAT);
	if (eatnow(philo))
		return(1);
	pthread_mutex_unlock(&philo->shared->mtx[fork1]);
	pthread_mutex_unlock(&philo->shared->mtx[fork2]);
	return (0);
}


int	eatnow(t_philos *philo)
{
	philo->lasteat = (philo->shared->ctime.tv_sec * 1000) + (philo->shared->ctime.tv_usec / 1000);
	if (nap(philo->shared->tteat, &philo->shared->finish, philo->shared->pnum))
			return (1);
	if (philo->teaten > 0)
		philo->teaten--;
	return (0);
}
