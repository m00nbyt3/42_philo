/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycarro <ycarro@student.42.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:30:12 by ycarro            #+#    #+#             */
/*   Updated: 2022/02/09 16:09:08 by ycarro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

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
