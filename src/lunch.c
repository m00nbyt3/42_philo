/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2022/12/14 16:09:32 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lunchtime(t_philos *philo, t_iforks *iforks);
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
		sprint(philo, PEAT);
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
		sprint(philo, PEAT);
		eatnow(philo);
		pthread_mutex_unlock(&philo->shared->mtx[iforks->right]);
		pthread_mutex_unlock(&philo->shared->mtx[iforks->left]);
	}
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
