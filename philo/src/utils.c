/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:56:21 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/17 11:40:54 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	timer(t_var *var)
{
	long	time;
	
	time = get_time_in_ms();
	time = time - var->start;
	return (time);
}

int	ft_atoi(const char *str)
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
	return (n * res);
}

void	destroy_forks(pthread_mutex_t *forks, int nb_forks)
{
	int i;

	i = 0;
	if (forks == NULL)
		return ;
	while (i < nb_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	free_all(t_var *var)
{
	destroy_forks(var->forks, var->nb_philo + 1);
	free(var);
}