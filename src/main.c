/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:33:38 by ycarro            #+#    #+#             */
/*   Updated: 2022/01/31 16:39:35 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*whoami(void *arg);
void	inittask(t_info *info, int pnum);
void	asigntask(t_philos *philo);
void	printtask(t_philos *philo);

int	main(int argc, char const *argv[])
{
	t_philos	*philos;
	t_info		info;
	int pnum;
	int	timeto;
	int j;
	

	if (argc != 3)
	{
		printf("ERROR\n");
		return (0);
	}
	//pthread_mutex_init(&mtx, 0);
	pnum = ft_atoi(argv[1]);
	timeto = ft_atoi(argv[2]);
	philos = malloc(pnum * sizeof(t_philos));
	nap(timeto);
	inittask(&info, pnum);
	j = 0;
	while (j < pnum)
	{
		philos[j].id = j;
		philos[j].status = &info;
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
	asigntask(philo);
	printtask(philo);
	return 0;
}

void	inittask(t_info *info, int pnum)
{
	int	tmp;

	info->iseating = malloc(pnum * sizeof(int));
	tmp = 0;
	while(tmp++ != pnum)
		info->iseating[tmp] = 0;
	info->isthinking = malloc(pnum * sizeof(int));
	tmp = 0;
	while(tmp++ != pnum)
		info->isthinking[tmp] = 0;
	info->issleeping = malloc(pnum * sizeof(int));
	tmp = 0;
	while(tmp++ != pnum)
		info->issleeping[tmp] = 0;
	info->pnum = pnum;
}

void	asigntask(t_philos *philo)
{
	int i;

	i = 0;
	while (philo->status->iseating[i] == 0 && i != (philo->id + 1))
		if (i++ == (philo->id))
		{
			philo->status->iseating[philo->id] = 1;
			return ;
		}
	i = 0;
	while (philo->status->isthinking[i] == 0 && i != (philo->id + 1))
		if (i++ == (philo->id))
		{
			philo->status->isthinking[philo->id] = 1;
			return ;
		}
	i = 0;
	while (philo->status->issleeping[i] == 0 && i != (philo->id + 1))
		if (i++ == (philo->id))
		{
			philo->status->issleeping[philo->id] = 1;
			return ;
		}
}

void	printtask(t_philos *philo)
{
	if (philo->status->iseating[philo->id] == 1)
		printf("Philosopher %d is eating\n", philo->id + 1);
	if (philo->status->isthinking[philo->id] == 1)
			printf("Philosopher %d is thinking\n", philo->id + 1);
	if (philo->status->issleeping[philo->id] == 1)
		printf("Philosopher %d is sleeping\n", philo->id + 1);
}