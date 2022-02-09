/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:34:58 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/09 15:19:41 by ycarro           ###   ########.fr       */
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
	pthread_mutex_t *mtx;
	int	tteat;
	int	ttthink;
	int	ttsleep;
}				t_info;

typedef struct s_philos
{
	pthread_t		th;
	int				id;
	t_info			*status;

}				t_philos;

typedef struct s_iforks
{
	int	tot;
	int	left;
	int	right;
}				t_iforks;

//Functions
void	*whoami(void *arg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	nap(int secs);
void	inittask(t_info *info, int pnum);
void	launchtime (t_philos *philo, t_iforks *iforks);
void	canieat(t_philos *philo, int *tot, int fstfork, int lstfork);


#endif