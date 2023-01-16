/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:30:12 by ycarro            #+#    #+#             */
/*   Updated: 2023/01/16 14:44:32 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		isnum(int argc, char **argv);
void	sprint(t_philos *philo, char *action);

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

int	isnum(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	sprint(t_philos *philo, char *action)
{
	pthread_mutex_lock(&philo->shared->plock);
	if (philo->shared->finish && action[7] != 'd')
	{
		pthread_mutex_unlock(&philo->shared->plock);
		return ;
	}
	gettimeofday(&(philo->shared->ctime), NULL);
	philo->showtime = ((philo->shared->ctime.tv_sec * 1000) \
	+ (philo->shared->ctime.tv_usec / 1000)) - philo->shared->inittime;
	printf(action, philo->showtime, (philo->id + 1));
	pthread_mutex_unlock(&philo->shared->plock);
}
