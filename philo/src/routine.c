/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:37:29 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/18 14:50:09 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mutex_print(t_philo *philo, char *action)
{
	long	time;
	int		temp;

	pthread_mutex_lock(&philo->var->print);
	time = timer(philo->var);
	pthread_mutex_lock(&philo->var->check_death);
	temp = philo->var->death;
	pthread_mutex_unlock(&philo->var->check_death);
	if (temp == 0)
	{
		pthread_mutex_unlock(&philo->var->print);
		return ;
	}
	printf("%ld %d %s", time, philo->id, action);
	pthread_mutex_unlock(&philo->var->print);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->f_right);
		mutex_print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->f_left);
		mutex_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->f_left);
		mutex_print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->f_right);
		mutex_print(philo, "has taken a fork\n");
	}
}

void	philo_eat(t_philo *philo)
{
	mutex_print(philo, "is eating\n");
	sleep_ms(philo->var->t_eat);
	pthread_mutex_lock(&philo->change_eat);
	philo->t_last_eat = get_time_in_ms();
	philo->nb_ate++;
	pthread_mutex_unlock(&philo->change_eat);
	pthread_mutex_unlock(philo->f_right);
	pthread_mutex_unlock(philo->f_left);
}

void	philo_sleep(t_philo *philo)
{
	mutex_print(philo, "is sleeping\n");
	sleep_ms(philo->var->t_sleep);
}

void	*philo_routine(void *philosophe)
{
	t_philo	*philo;
	int		temp;

	philo = philosophe;
	if (philo->var->nb_philo == 1)
	{
		mutex_print(philo, "has taken a fork\n");
		sleep_ms(philo->var->t_eat);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		sleep_ms(100);
	while (1)
	{
		take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		mutex_print(philo, "is thinking\n");
		pthread_mutex_lock(&philo->var->check_death);
		temp = philo->var->death;
		pthread_mutex_unlock(&philo->var->check_death);
		if (temp == 0)
			break ;
	}
	return (NULL);
}
