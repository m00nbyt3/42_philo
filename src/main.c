/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:33:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/03 12:49:17 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*whoami(void *arg);
void	inittask(t_info *info, t_philos *philos, int pnum);
void	launchtime (t_philos *philo);
void	printtask(t_philos *philo);

int	main(int argc, char const *argv[])
{
	t_philos	*philos;
	t_info		info;
	int pnum;
	int j;
	

	if (argc != 3)
	{
		printf("ERROR\n");
		return (0);
	}
	pnum = ft_atoi(argv[1]);
	info.ttsleep = ft_atoi(argv[2]);
	philos = malloc(pnum * sizeof(t_philos));
	inittask(&info, philos, pnum);
	j = 0;
	while (j < pnum)
	{
		philos[j].id = j;
		philos[j].status = &info;
		usleep(50);
		pthread_create(&philos[j].th, 0, whoami, &philos[j]);
		j++;
	}
	j = 0;
	while (j < pnum)
	{
		pthread_join(philos[j].th, 0);
		j++;
	}
	return 0;
}

void	*whoami(void *arg)
{
	t_philos *philo;
 
	philo = (t_philos *)arg;
	launchtime (philo);
	return 0;
}

void	inittask(t_info *info, t_philos *philos, int pnum)
{
	int i;

	info->pnum = pnum;
	info->fork = malloc (pnum * sizeof(int));
	i = 0;
	while (i < pnum)
	{
		info->fork[i] = 1;
		pthread_mutex_init(&philos[i].mtx, 0);
		if (i != 0)
			philos[i - 1].mtx2 = &philos[i].mtx;
		if (i == pnum - 1)
			philos[i].mtx2 = &philos[0].mtx;
		i++;
	}
}

void	launchtime (t_philos *philo)
{
	int	tot;
	int steal;

	steal = philo->id + 1;
	if (philo->id == (philo->status->pnum - 1))
		steal = 0;
	tot = 0;
	while (tot < 2)
	{
		//printf("mtx1\n");

		pthread_mutex_lock(&philo->mtx);
		if (philo->status->fork[philo->id])
		{
			printf("Philospher %d has taken a fork 🥄\n", philo->id);
			philo->status->fork[philo->id] = 0;
			tot++;
		}
		//printf("mtx2\n");

		pthread_mutex_unlock(&philo->mtx);
		pthread_mutex_lock(philo->mtx2);
		if (philo->status->fork[steal])
		{
			printf("Philospher %d has taken a fork 🥄\n", philo->id);
			philo->status->fork[steal] = 0;
			tot++;
		}
		//printf("value %d\n", philo->status->fork[philo->id + 1]);
		//printf("here\n");
		pthread_mutex_unlock(philo->mtx2);
	}
	printf("Philosopher %d is eating 🍴\n", philo->id);
	nap(philo->status->ttsleep);
	printf("Philosopher %d is sleeping 💤\n", philo->id);
	pthread_mutex_lock(&philo->mtx);
	pthread_mutex_lock(philo->mtx2);
	philo->status->fork[philo->id] = 1;
	philo->status->fork[philo->id + 1] = 1;
	pthread_mutex_unlock(&philo->mtx);
	pthread_mutex_unlock(philo->mtx2);
}
