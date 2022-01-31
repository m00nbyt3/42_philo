/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:34:58 by ycarro            #+#    #+#             */
/*   Updated: 2022/01/31 15:56:44 by ycarro           ###   ########.fr       */
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
	int			pnum;
	int			*iseating;
	int			*isthinking;
	int			*issleeping;
}				t_info;

typedef struct s_philos
{
	pthread_t	th;
	int			id;
	int 		last_eat;
	t_info		*status;

}				t_philos;

//Functions
void	*whoami(void *arg);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	nap(int secs);
void	inittask(t_info *info, int pnum);
void	asigntask(t_philos *philo);
void	printtask(t_philos *philo);

#endif