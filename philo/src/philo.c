/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:26:49 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/16 16:27:57 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	take_forks(t_philo *philo)
{
	if (philo->p_id % 2 == 1)
	{
		pthread_mutex_lock(philo->f_left);
		printf("%ld %d has taken a fork", get_time_in_ms(), philo->p_id);
		pthread_mutex_lock(philo->f_right);
		printf("%ld %d has taken a fork", get_time_in_ms(), philo->p_id);
	}
	else
	{
		pthread_mutex_lock(philo->f_right);
		printf("%ld %d has taken a fork", get_time_in_ms(), philo->p_id);
		pthread_mutex_lock(philo->f_left);
		printf("%ld %d has taken a fork", get_time_in_ms(), philo->p_id);
	}
}

void	philo_eat(t_philo *philo)
{
	printf("%ld %d is eating", get_time_in_ms(), philo->p_id);
	usleep(philo->p_var->t_eat * 1000);
	philo->t_last_eat = get_time_in_ms();
	philo->nb_ate++;
}

void	*philo_routine(void *philosophe)
{
	t_philo	*philo;

	philo = philosophe;
	while (1)
	{
		take_forks(philo);
		philo_eat(philo);
	}
	return (NULL);
}

pthread_mutex_t *init_fork(int nb_forks)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nb_forks);
	if (!forks)
		return (NULL);
	while (i < nb_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

t_philo *init_philos(int nb_philos, t_var *var)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * nb_philos);
	while (i < nb_philos)
	{
		philos[i].p_id = i;
		philos[i].f_left = &(var->forks[i]);
		philos[i].f_right = &(var->forks[(i + 1) % nb_philos]);
		philos[i].nb_ate = 0;
		philos[i].t_last_eat = 0;
		philos[i].p_var = var;
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	return (philos);
}

t_var *init_var(t_var *var, char **argv, int argc)
{
	var = malloc(sizeof(t_var) * 1);
	var->nb_philo = ft_atoi(argv[1]);
	var->t_death = ft_atoi(argv[2]);
	var->t_eat = ft_atoi(argv[3]);
	var->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var->nb_eat = ft_atoi(argv[5]);
	var->forks = init_fork(var->nb_philo);
	var->philos = init_philos(var->nb_philo, var);
	return (var);
}

int main(int argc, char **argv)
{
	t_var *var;
	
	var = NULL;
	if (argc > 6 || argc < 5)
		return (0);
	var = init_var(var, argv, argc);
	pthread_join(var->philos[0].thread, NULL);
	return (free_all(var), 0);
}