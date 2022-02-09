/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:33:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/09 15:32:37 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*whoami(void *arg);
void	inittask(t_info *info, int pnum);
void	launchtime (t_philos *philo, t_iforks *iforks);
void	canieat(t_philos *philo, int *tot, int fstfork, int lstfork);


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
	philos = malloc((pnum) * sizeof(t_philos));
	inittask(&info, pnum);
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
	t_philos	*philo;
	t_iforks	iforks;

	philo = (t_philos *)arg;
	iforks.left = philo->id;
	if (philo->id == (philo->status->pnum - 1))
		iforks.right = 0;
	else
		iforks.right = philo->id + 1;
	iforks.tot = 0;
	launchtime (philo, &iforks);
	return 0;
}

void	inittask(t_info *info, int pnum)
{
	int i;

	info->pnum = pnum;
	info->fork = malloc (pnum * sizeof(int));
	info->mtx = malloc (pnum * sizeof(pthread_mutex_t));
	i = 0;
	while (i < pnum)
	{
		info->fork[i] = 1;
		pthread_mutex_init(&info->mtx[i], 0);
		i++;
	}
}

void	launchtime (t_philos *philo, t_iforks *iforks)
{
	while (iforks->tot < 2)
	{
		pthread_mutex_lock(&philo->status->mtx[iforks->left]);
		if (philo->status->fork[iforks->left])
		{
			canieat(philo, &iforks->tot, iforks->right, iforks->left);
			if (iforks->tot == 2)
				break;
		}
		pthread_mutex_unlock(&philo->status->mtx[iforks->left]);
		pthread_mutex_lock(&philo->status->mtx[iforks->right]);
		if (philo->status->fork[iforks->right])
		{
			canieat(philo, &iforks->tot, iforks->left, iforks->right);
			if (iforks->tot == 2)
				break;
		}
		pthread_mutex_unlock(&philo->status->mtx[iforks->right]);
	}
}

void	canieat(t_philos *philo, int *tot, int fstfork, int lstfork)
{
	printf("Philospher %d has taken a fork🥄\n", philo->id);
	philo->status->fork[lstfork] = 0;
	(*tot)++;
	if (*tot == 2)
	{
		printf("Philosopher %d is eating 🍴\n", philo->id);
		nap(philo->status->ttsleep);
		printf("(DEBUG) Philosopher %d finished eating :P\n", philo->id);
		philo->status->fork[fstfork] = 1;
		philo->status->fork[lstfork] = 1;
		//printf("Philosopher %d is sleeping💤\n", philo->id);
		pthread_mutex_unlock(&philo->status->mtx[lstfork]);
	}
}