/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:26:49 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/17 19:29:59 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_var *var)
{
	int		i;
	long	time;
	long	temp;

	i = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_lock(&var->change_eat);
		temp = var->philos[i].t_last_eat;
		pthread_mutex_unlock(&var->change_eat);
		time = get_time_in_ms();
		if ((time - temp) > var->t_death)
		{			
			mutex_print(&var->philos[i], "died\n");
			pthread_mutex_lock(&var->check_death);
			var->death = 0;
			pthread_mutex_unlock(&var->check_death);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_nb_eat(t_var *var)
{
	int	i;
	int count;
	int	temp;

	i = 0;
	count = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_lock(&var->change_eat);
		temp = var->philos[i].nb_ate;
		pthread_mutex_unlock(&var->change_eat);
		if (var->philos[i].nb_ate >= var->nb_eat)
			count++;
		i++;
		if (count >= var->nb_philo)
			return (1);
	}
	return (0);
}

void	check_conditions(t_var *var)
{
	sleep_ms(var->t_death);
	while (1)
	{
		if (check_death(var) == 1)
			break ;
		if (var->nb_eat != -1 && check_nb_eat(var) == 1)
		{
			pthread_mutex_lock(&var->check_death);
			var->death = 0;
			pthread_mutex_unlock(&var->check_death);
			break ;
		}	
	}
}

void	free_all(t_var *var)
{
	destroy_forks(var->forks, var->nb_philo + 1);
	// free(var->philos);
	free(var);
}

int main(int argc, char **argv)
{
	t_var	*var;
	int		i;
	
	var = NULL;
	i = 0;
	if (argc > 6 || argc < 5)
		return (0);
	var = init_var(var, argv, argc);
	check_conditions(var);
	while (i < var->nb_philo)
	{
		pthread_join(var->philos[i].thread, NULL);
		i++;
	}
	return (free_all(var), 0);
}