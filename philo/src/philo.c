/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:26:49 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/18 14:49:46 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_var *var)
{
	destroy_mutex(var, var->nb_philo);
	free(var->philos);
	free(var);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] < '0' || argv[i][0] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	*var;
	int		i;

	var = NULL;
	i = 0;
	if (argc > 6 || argc < 5 || check_args(argc, argv) == 1)
	{
		printf("Arguments should be : <number_of_philosophers> <time_to_die> "
			"<time_to_eat> <time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	var = init_var(var, argv, argc);
	check_conditions(var);
	while (i < var->nb_philo)
	{
		pthread_join(var->philos[i].thread, NULL);
		i++;
	}
	return (free_all(var), 0);
}
