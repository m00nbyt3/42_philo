/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:33:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/10 12:26:21 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philolife(void *arg);
void	inittask(t_info *info, int pnum);
void	launchtime(t_philos *philo, t_iforks *iforks);
void	canieat(t_philos *philo, int *tot, int fstfork, int lstfork);
void	timepassed(t_philos *philos);

int	main(int argc, char const *argv[])
{
	t_philos	*philos;
	t_info		info;
	int			pnum;
	int			j;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR\n");
		return (0);
	}
	pnum = ft_atoi(argv[1]);
	info.ttdie = ft_atoi(argv[2]);
	info.tteat = ft_atoi(argv[3]);
	info.ttsleep = ft_atoi(argv[4]);;
	philos = malloc((pnum) * sizeof(t_philos));
	inittask(&info, pnum);
	j = 0;
	while (j < pnum)
	{
		philos[j].id = j;
		philos[j].status = &info;
		usleep(50);
		gettimeofday(&(info.ctime), NULL);
		philos[j].lasteat = info.ctime.tv_sec;
		pthread_create(&philos[j].th, 0, philolife, &philos[j]);
		j++;
	}
	j = 0;
	/*while (j < pnum)
	{
		pthread_join(philos[j].th, 0);
		j++;
	}*/
	timepassed(philos);
	return (0);
}

void	*philolife(void *arg)
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
	while (1)
	{
		launchtime (philo, &iforks);
		printf("Philosopher %d is sleeping 💤\n", philo->id);
		nap(philo->status->ttsleep);
		printf("Philosopher %d is thinking 🤔\n", philo->id);
	}
	return (0);
}

void	inittask(t_info *info, int pnum)
{
	int	i;

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

void	launchtime(t_philos *philo, t_iforks *iforks)
{
	iforks->tot = 0;
	while (iforks->tot < 2)
	{
		pthread_mutex_lock(&philo->status->mtx[iforks->left]);
		if (philo->status->fork[iforks->left])
		{
			canieat(philo, &iforks->tot, iforks->right, iforks->left);
			if (iforks->tot == 2)
				break ;
		}
		pthread_mutex_unlock(&philo->status->mtx[iforks->left]);
		pthread_mutex_lock(&philo->status->mtx[iforks->right]);
		if (philo->status->fork[iforks->right])
		{
			canieat(philo, &iforks->tot, iforks->left, iforks->right);
			if (iforks->tot == 2)
				break ;
		}
		pthread_mutex_unlock(&philo->status->mtx[iforks->right]);
	}
}

void	canieat(t_philos *philo, int *tot, int fstfork, int lstfork)
{
	printf("Philospher %d has taken a fork 🥄\n", philo->id);
	philo->status->fork[lstfork] = 0;
	(*tot)++;
	if (*tot == 2)
	{
		printf("Philosopher %d is eating 🍴\n", philo->id);
		nap(philo->status->tteat);
		printf("(DEBUG) Philosopher %d finished eating :P\n", philo->id);
		gettimeofday(&(philo->status->ctime), NULL);
		philo->lasteat = philo->status->ctime.tv_sec;
		philo->status->fork[fstfork] = 1;
		philo->status->fork[lstfork] = 1;
		pthread_mutex_unlock(&philo->status->mtx[lstfork]);
	}
}

void	timepassed(t_philos *philos)
{
	int	i;
	long	actual;

	while (1)
	{
		usleep(5000);
		i = 0;		
		while (i < philos[0].status->pnum)
		{
			gettimeofday(&(philos[0].status->ctime), NULL);
			actual = philos[0].status->ctime.tv_sec;
			actual -= philos[i].lasteat;
			if (actual > philos[i].status->ttdie)
			{
				printf("Philosopher %d died 💀\n", philos[i].id);
				exit(0);
			}
			i++;
		}
	}
}