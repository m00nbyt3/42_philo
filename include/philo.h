/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:34:58 by ycarro            #+#    #+#             */
/*   Updated: 2022/12/20 12:42:22 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//Header files
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

//Definitions
# define PDIE "%ld %d died\n"
# define PEAT "%ld %d is eating\n"
# define PTFORK "%ld %d has taken a fork\n"	
# define PSLEEP "%ld %d is sleeping\n"
# define PTHINK "%ld %d is thinking\n"

//Structs
typedef struct s_info
{
	struct timeval	ctime;
	long			inittime;
	int				pnum;
	int				*forks;
	pthread_mutex_t	*mtx;
	pthread_mutex_t	plock;
	int				tteat;
	int				ttsleep;
	long			ttdie;
	int				maxeat;
	int				finish;
}				t_info;

typedef struct s_philos
{
	pthread_t		th;
	int				id;
	int				teaten;
	long			lasteat;
	long			showtime;
	t_info			*shared;

}				t_philos;

typedef struct s_iforks
{
	int	left;
	int	right;
}				t_iforks;

//Functions
void	*philolife(void *arg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		nap(long msecs, int *imdead, int towait);
int		s_nap(long msecs);
void	inittask(int argc, char **argv, t_info *info);
void	pbirth(t_philos *philos, t_info *info);
int		lunchtime(t_philos *philo, t_iforks *iforks);
int		eatnow(t_philos *philo);
void	timepassed(t_philos *philos);
void	sprint(t_philos *philo, char *action);
void	freeall(t_philos *philos);

#endif