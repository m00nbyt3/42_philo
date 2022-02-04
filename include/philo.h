/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:34:58 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/03 12:38:36 by ycarro           ###   ########.fr       */
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
#include <sys/time.h>

//Structs

typedef struct s_info
{
	int	pnum;
	int	*fork;
	int	tteat;
	int	ttthink;
	int	ttsleep;
}				t_info;

typedef struct s_philos
{
	pthread_t		th;
	pthread_mutex_t mtx;
	pthread_mutex_t *mtx2;
	int				id;
	t_info			*status;

}				t_philos;

//Functions
void	*whoami(void *arg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	nap(int secs);
void	inittask(t_info *info, t_philos *philos, int pnum);
void	launchtime(t_philos *philo);
void	printtask(t_philos *philo);

#endif