/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:56:21 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/18 15:13:07 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	timer(t_var *var)
{
	long	time;

	time = get_time_in_ms();
	time = time - var->start;
	return (time);
}

int	ft_atoi(const char *str, int utils)
{
	int	i;
	int	res;
	int	n;

	res = 0;
	n = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (utils == 1 && str[i])
		return (-1);
	return (n * res);
}

void	destroy_mutex(t_var *var, int nb_forks)
{
	int	i;

	i = 0;
	while (i < nb_forks)
	{
		pthread_mutex_destroy(&var->forks[i]);
		pthread_mutex_destroy(&var->philos[i].change_eat);
		i++;
	}
	pthread_mutex_destroy(&var->check_death);
	pthread_mutex_destroy(&var->print);
	free(var->forks);
}

void	sleep_ms(int duration)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() < start + duration)
		usleep(500);
}
