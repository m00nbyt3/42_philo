/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2022/12/13 15:02:05 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launchtime(t_philos *philo, t_iforks *iforks);
int	eatnow(t_philos *philo);

int	launchtime(t_philos *philo, t_iforks *iforks)
{
	if (philo->shared->finish)
			return (1);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->shared->mtx[iforks->left]);
		sprint(philo, PTFORK);
		pthread_mutex_lock(&philo->shared->mtx[iforks->right]);
		sprint(philo, PTFORK);
		eatnow(philo);
		pthread_mutex_unlock(&philo->shared->mtx[iforks->left]);
		pthread_mutex_unlock(&philo->shared->mtx[iforks->right]);
	}
	else
	{
		pthread_mutex_lock(&philo->shared->mtx[iforks->right]);
		sprint(philo, PTFORK);
		pthread_mutex_lock(&philo->shared->mtx[iforks->left]);
		sprint(philo, PTFORK);
		eatnow(philo);
		pthread_mutex_unlock(&philo->shared->mtx[iforks->right]);
		pthread_mutex_unlock(&philo->shared->mtx[iforks->left]);
	}
	return (0);
}


int	eatnow(t_philos *philo)
{
	sprint(philo, PEAT);
	if (nap(philo->shared->tteat, &philo->shared->finish))
			return (1);
	philo->lasteat = (philo->shared->ctime.tv_sec * 1000) + (philo->shared->ctime.tv_usec / 1000);	
	if (philo->teaten > 0)
		philo->teaten--;
	return (0);
}
