/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:43:13 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/18 15:12:25 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	*init_fork(int nb_forks)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nb_forks + 1);
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

t_philo	*init_philos(int nb_philos, t_var *var)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * nb_philos);
	while (i < nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].f_left = &(var->forks[i]);
		philos[i].f_right = &(var->forks[(i + 1) % nb_philos]);
		philos[i].nb_ate = 0;
		philos[i].t_last_eat = get_time_in_ms();
		philos[i].var = var;
		pthread_mutex_init(&philos[i].change_eat, NULL);
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	return (philos);
}

t_var	*init_var(t_var *var, char **argv, int argc)
{
	var = malloc(sizeof(t_var) * 1);
	var->nb_philo = ft_atoi(argv[1], 0);
	var->t_death = ft_atoi(argv[2], 0);
	var->t_eat = ft_atoi(argv[3], 0);
	var->t_sleep = ft_atoi(argv[4], 0);
	var->nb_eat = -1;
	if (argc == 6)
		var->nb_eat = ft_atoi(argv[5], 0);
	var->start = get_time_in_ms();
	var->death = 1;
	pthread_mutex_init(&var->check_death, NULL);
	pthread_mutex_init(&var->print, NULL);
	var->forks = init_fork(var->nb_philo);
	var->philos = init_philos(var->nb_philo, var);
	return (var);
}
