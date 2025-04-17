/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:37:29 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/17 11:43:41 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->f_left);
		printf("%ld %d has taken a fork\n", timer(philo->var), philo->id);
		pthread_mutex_lock(philo->f_right);
		printf("%ld %d has taken a fork\n", timer(philo->var), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->f_right);
		printf("%ld %d has taken a fork\n", timer(philo->var), philo->id);
		pthread_mutex_lock(philo->f_left);
		printf("%ld %d has taken a fork\n", timer(philo->var), philo->id);
	}
}

void	philo_eat(t_philo *philo)
{
	printf("%ld %d is eating\n", timer(philo->var), philo->id);
	usleep(philo->var->t_eat * 1000);
	philo->t_last_eat = get_time_in_ms();
	philo->nb_ate++;
	pthread_mutex_unlock(philo->f_right);
	pthread_mutex_unlock(philo->f_left);
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", timer(philo->var), philo->id);
	usleep(philo->var->t_sleep * 1000);
}

void	*philo_routine(void *philosophe)
{
	t_philo	*philo;

	philo = philosophe;
	while (philo->death)
	{
		take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		printf("%ld %d is thinking\n", timer(philo->var), philo->id);
	}
	return (NULL);
}
