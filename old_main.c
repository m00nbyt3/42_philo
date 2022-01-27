/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:59:07 by ycarro            #+#    #+#             */
/*   Updated: 2022/01/24 12:32:59 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>

void	*func1(void *arg);
void	*whoami(void *arg);

#define BIG 1000000000UL
uint32_t counter = 0;
pthread_mutex_t	mtx;

void *mycount(void *arg);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

int	main(int argc, char const *argv[])
{
	int i;
	int j;
	int	k;

	if (argc != 3)
	{
		printf("ERROR\n");
		return (0);
	}
	pthread_mutex_init(&mtx, 0);
	i = ft_atoi(argv[1]);
	k = ft_atoi(argv[2]);
	pthread_t	th[i];
	j = 0;
	while (j < i)
	{
		pthread_create(&th[j], 0, whoami, &j);
		//usleep(100);
		j++;
	}
	j = 0;
	while (j < i)
	{
		pthread_join(th[j], 0);
		j++;
	}
	//pthread_join(th[1], 0);

	//pthread_create(&th1, 0, mycount, 0);
	//pthread_create(&th2, 0, func1, 0);
	//pthread_join(th1, 0);
	//mycount(0);
	//pthread_join(th1, 0);
	//printf("NUM: %u\n", counter);
	return 0;
}

void	*whoami(void *arg)
{
	int num;
 	int lp;

 	
	num = *(int *)arg;
	printf("I am philosopher %d\n", num + 1);

	if (num % 2)
		lp = 1;
	else
		lp = 0;
	/*while (1)
	{	
		pthread_mutex_lock(&mtx);
		printf("I am philosopher %d, ", num + 1);
		if (lp)
		{
			printf("Im eating\n");
			lp--;
		}
		else
		{
			printf("Im sleeping\n");
			lp++;
		}
		pthread_mutex_unlock(&mtx);
		usleep(1000000);
	}*/
	return 0;
}

void	*func1(void *arg)
{
	int i;

	i = *(int *)(arg);
	while (i)
	{
		printf("Loop %d\n", i);
		i--;
	}
	return 0;
}

void *mycount(void *arg)
{
	int i;

	i = 0;
	while(i < BIG)
	{
		i++;
		pthread_mutex_lock(&mtx);
		counter++;
		pthread_mutex_unlock(&mtx);
	}
	return 0;
}

int	ft_atoi(const char *str)
{
	int				sign;
	long long		num;

	sign = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit((int)*str))
	{
		num = (num * 10) + (*str - '0');
		if ((num * sign) > INT_MAX)
			return (-1);
		else if ((num * sign) < INT_MIN)
			return (0);
		str++;
	}
	return (num * sign);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}
