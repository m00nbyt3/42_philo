/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:34:58 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/15 15:01:43 by ycarro           ###   ########.fr       */
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

//Structs

typedef struct s_info
{
	struct timeval	ctime;
	long			inittime;
	int				pnum;
	int				*fork;
	pthread_mutex_t	*mtx;
	int				tteat;
	int				ttsleep;
	long			ttdie;
	int				finish;
}				t_info;

typedef struct s_philos
{
	pthread_t		th;
	int				id;
	long			lasteat;
	long			showtime;
	t_info			*status;

}				t_philos;

typedef struct s_iforks
{
	int	tot;
	int	left;
	int	right;
}				t_iforks;

//Functions
void	*philolife(void *arg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		nap(int secs, int *imdead);
void	inittask(t_info *info, int pnum);
int		launchtime(t_philos *philo, t_iforks *iforks);
int		canieat(t_philos *philo, int *tot, int fstfork, int lstfork);
void	timepassed(t_philos *philos);

#endif