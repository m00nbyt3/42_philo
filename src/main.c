/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:33:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/17 15:12:31 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philolife(void *arg);
void	pbirth(t_philos *philos, t_info *info);
void	inittask(int argc, char **argv, t_info *info);
void	needfood(t_philos *philo);
void	freeall(t_philos *philos);

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_info		info;
	int			j;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR\n");
		return (0);
	}
	inittask(argc, argv, &info);
	philos = malloc((info.pnum) * sizeof(t_philos));
	pbirth(philos, &info);
	timepassed(philos);
	j = 0;
	while (j < info.pnum)
	{
		pthread_join(philos[j].th, 0);
		j++;
	}
	freeall(philos);
	return (0);
}

void	inittask(int argc, char **argv, t_info *info)
{
	int	i;

	info->pnum = ft_atoi(argv[1]);
	info->ttdie = ft_atoi(argv[2]) * 1000;
	info->tteat = ft_atoi(argv[3]);
	info->ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->maxeat = ft_atoi(argv[5]);
	else
		info->maxeat = -1;
	info->finish = 0;
	info->fork = malloc (info->pnum * sizeof(int));
	info->mtx = malloc (info->pnum * sizeof(pthread_mutex_t));
	i = 0;
	while (i < info->pnum)
	{
		info->fork[i] = 1;
		pthread_mutex_init(&info->mtx[i], 0);
		i++;
	}
	pthread_mutex_init(&info->plock, 0);
	gettimeofday(&(info->ctime), NULL);
	info->inittime = ((info->ctime.tv_sec * 1000000) + info->ctime.tv_usec) / 1000;
}

void	pbirth(t_philos *philos, t_info *info)
{
	int j;

	j = 0;
	while (j < info->pnum)
	{
		philos[j].id = j;
		philos[j].shared = info;
		philos[j].teaten = info->maxeat;
		//nap(0.5, &philos[0].shared->finish);
		usleep(50);
		gettimeofday(&(info->ctime), NULL);
		philos[j].lasteat = (info->ctime.tv_sec * 1000000) + info->ctime.tv_usec;
		pthread_create(&philos[j].th, 0, philolife, &philos[j]);
		j++;
	}
}

void	*philolife(void *arg)
{
	t_philos	*philo;
	t_iforks	iforks;

	philo = (t_philos *)arg;
	iforks.left = philo->id;
	if (philo->id == (philo->shared->pnum - 1))
		iforks.right = 0;
	else
		iforks.right = philo->id + 1;
	iforks.tot = 0;
	while (1)
	{
		if (philo->shared->finish)
			return (0);
		needfood(philo);
		if (launchtime (philo, &iforks))
			return (0);
		if (!philo->teaten)
			break ;
		sprint(philo, PSLEEP);
		if (nap(philo->shared->ttsleep, &philo->shared->finish))
			return (0);
		sprint(philo, PTHINK);
	}
	return (0);
}

void	needfood(t_philos *philo)
{
	int	i;
	long	actual;
	struct timeval	ctime;

	while (1)
	{
		i = 0;		
		gettimeofday(&ctime, NULL);
		actual = (ctime.tv_sec * 1000000) + ctime.tv_usec;
		actual -= philo->lasteat;
		if ((philo->shared->ttdie + 50) > actual)
			return ;
		if (!philo->teaten)
			return ;
		i++;
	}
}

void	freeall(t_philos *philos)
{
	free(philos[0].shared->fork);
	free(philos[0].shared->mtx);
	free(philos);
}
