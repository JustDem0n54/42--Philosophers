/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:26:49 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/17 11:44:39 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_var *var)
{
	int		i;
	long	time;

	i = 0;
	while (i < var->nb_philo)
	{
		time = get_time_in_ms();
		if ((time - var->philos[i].t_last_eat) > var->t_death)
		{
			var->philos[i].death = 0;
			printf("%ld %d died\n", timer(var), var->philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_nb_eat(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		if (var->philos[i].nb_ate == var->nb_eat)
			return (1);
		i++;
	}
	return (0);
}

void	check_conditions(t_var *var)
{
	usleep(var->t_death * 1000);
	while (1)
	{
		if (check_death(var) == 1)
			break ;
		if (check_nb_eat(var) == 1)
			break ;
	}
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
	// while (i < var->nb_philo)
	// {
	// 	pthread_join(var->philos[i].thread, NULL);
	// 	i++;
	// }
	return (free_all(var), 0);
}