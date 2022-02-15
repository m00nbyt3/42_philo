/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:33:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/15 15:31:57 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philolife(void *arg);
void	inittask(t_info *info, int pnum);
int		launchtime(t_philos *philo, t_iforks *iforks);
int		canieat(t_philos *philo, int *tot, int fstfork, int lstfork);
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
	info.ttdie = ft_atoi(argv[2]) * 1000000;
	info.tteat = ft_atoi(argv[3]);
	info.ttsleep = ft_atoi(argv[4]);;
	info.finish = 0;
	philos = malloc((pnum) * sizeof(t_philos));
	inittask(&info, pnum);
	j = 0;
	while (j < pnum)
	{
		philos[j].id = j;
		philos[j].status = &info;
		usleep(50);
		gettimeofday(&(info.ctime), NULL);
		philos[j].lasteat = (info.ctime.tv_sec * 1000000) + info.ctime.tv_usec;
		pthread_create(&philos[j].th, 0, philolife, &philos[j]);
		j++;
	}
	timepassed(philos);
	j = 0;
	while (j < pnum)
	{
		pthread_join(philos[j].th, 0);
		j++;
	}
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
		if (philo->status->finish)
			return (0);
		if (launchtime (philo, &iforks))
			return (0);
		gettimeofday(&(philo->status->ctime), NULL);
		philo->showtime = (((philo->status->ctime.tv_sec * 1000000) \
		+ philo->status->ctime.tv_usec) / 1000) - philo->status->inittime;
		printf("%ld Philosopher %d is sleeping 💤\n", philo->showtime, philo->id);
		if (nap(philo->status->ttsleep, &philo->status->finish))
			return (0);
		gettimeofday(&(philo->status->ctime), NULL);
		philo->showtime = (((philo->status->ctime.tv_sec * 1000000) \
		+ philo->status->ctime.tv_usec) / 1000) - philo->status->inittime;
		printf("%ld Philosopher %d is thinking 🤔\n", philo->showtime, philo->id);
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
	gettimeofday(&(info->ctime), NULL);
	info->inittime = ((info->ctime.tv_sec * 1000000) + info->ctime.tv_usec) / 1000;
}

int	launchtime(t_philos *philo, t_iforks *iforks)
{
	iforks->tot = 0;
	while (iforks->tot < 2)
	{
		if (philo->status->finish)
			return (1);
		pthread_mutex_lock(&philo->status->mtx[iforks->left]);
		if (philo->status->fork[iforks->left])
		{
			if (canieat(philo, &iforks->tot, iforks->right, iforks->left))
			{
				pthread_mutex_unlock(&philo->status->mtx[iforks->left]);
				return (1);
			}
			if (iforks->tot == 2)
				break ;
		}
		pthread_mutex_unlock(&philo->status->mtx[iforks->left]);
		pthread_mutex_lock(&philo->status->mtx[iforks->right]);
		if (philo->status->fork[iforks->right])
		{
			if (canieat(philo, &iforks->tot, iforks->left, iforks->right))
			{
				pthread_mutex_unlock(&philo->status->mtx[iforks->right]);
				return (1);
			}
			if (iforks->tot == 2)
				break ;
		}
		pthread_mutex_unlock(&philo->status->mtx[iforks->right]);
	}
	return (0);
}

int	canieat(t_philos *philo, int *tot, int fstfork, int lstfork)
{
	gettimeofday(&(philo->status->ctime), NULL);
	philo->showtime = (((philo->status->ctime.tv_sec * 1000000) \
	+ philo->status->ctime.tv_usec) / 1000) - philo->status->inittime;
	printf("%ld Philospher %d has taken a fork 🥄\n", philo->showtime, philo->id);
	philo->status->fork[lstfork] = 0;
	(*tot)++;
	if (*tot == 2)
	{
		gettimeofday(&(philo->status->ctime), NULL);
		philo->showtime = (((philo->status->ctime.tv_sec * 1000000) \
		+ philo->status->ctime.tv_usec) / 1000) - philo->status->inittime;
		printf("%ld Philosopher %d is eating 🍴\n", philo->showtime, philo->id);
		if (nap(philo->status->tteat, &philo->status->finish))
			return (1);
		gettimeofday(&(philo->status->ctime), NULL);
		philo->lasteat = (philo->status->ctime.tv_sec * 1000000) + philo->status->ctime.tv_usec;
		philo->status->fork[fstfork] = 1;
		philo->status->fork[lstfork] = 1;
		pthread_mutex_unlock(&philo->status->mtx[lstfork]);
	}
	return (0);
}

void	timepassed(t_philos *philos)
{
	int	i;
	long	actual;

	while (1)
	{
		//nap(5 / 1000, &philos[0].status->finish);
		i = 0;		
		while (i < philos[0].status->pnum)
		{
			gettimeofday(&(philos[0].status->ctime), NULL);
			actual = (philos[0].status->ctime.tv_sec * 1000000) + philos[0].status->ctime.tv_usec;
			actual -= philos[i].lasteat;
			if (actual >= philos[i].status->ttdie)
			{
				philos[i].status->finish = 1;
				gettimeofday(&(philos[0].status->ctime), NULL);
				philos[0].showtime = (((philos[0].status->ctime.tv_sec * 1000000) \
				+ philos[0].status->ctime.tv_usec) / 1000) - philos[0].status->inittime;
				printf("%ld Philosopher %d died 💀\n", philos[0].showtime, philos[i].id);
				return ;
			}
			i++;
		}
	}
}
