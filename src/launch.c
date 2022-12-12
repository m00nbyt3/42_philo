/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:31:13 by ycarro            #+#    #+#             */
/*   Updated: 2022/11/15 17:10:14 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launchtime(t_philos *philo, t_iforks *iforks);
int	canieat(t_philos *philo, int *tot, int fstfork, int lstfork);

int	launchtime(t_philos *philo, t_iforks *iforks)
{
	iforks->tot = 0;
	while (iforks->tot < 2)
	{
		if (philo->shared->finish)
			return (1);
		pthread_mutex_lock(&philo->shared->mtx[iforks->left]);
		if (philo->shared->fork[iforks->left])
		{
			if (canieat(philo, &iforks->tot, iforks->right, iforks->left))
			{
				pthread_mutex_unlock(&philo->shared->mtx[iforks->left]);
				return (1);
			}
			if (iforks->tot == 2)
				break ;
		}
		pthread_mutex_unlock(&philo->shared->mtx[iforks->left]);
		pthread_mutex_lock(&philo->shared->mtx[iforks->right]);
		if (philo->shared->fork[iforks->right])
		{
			if (canieat(philo, &iforks->tot, iforks->left, iforks->right))
			{
				pthread_mutex_unlock(&philo->shared->mtx[iforks->right]);
				return (1);
			}
			if (iforks->tot == 2)
				break ;
		}
		pthread_mutex_unlock(&philo->shared->mtx[iforks->right]);
	}
	return (0);
}

int	canieat(t_philos *philo, int *tot, int fstfork, int lstfork)
{
	sprint(philo, PTFORK);
	philo->shared->fork[lstfork] = 0;
	(*tot)++;
	if (*tot == 2)
	{
		sprint(philo, PEAT);
		if (nap(philo->shared->tteat, &philo->shared->finish))
			return (1);
		gettimeofday(&(philo->shared->ctime), NULL);
		philo->lasteat = (philo->shared->ctime.tv_sec * 1000000) + philo->shared->ctime.tv_usec;
		philo->shared->fork[fstfork] = 1;
		philo->shared->fork[lstfork] = 1;
		if (philo->teaten > 0)
			philo->teaten--;
		pthread_mutex_unlock(&philo->shared->mtx[lstfork]);
	}
	return (0);
}
