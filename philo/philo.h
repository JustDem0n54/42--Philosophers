/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:22:59 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/17 11:44:06 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*f_left;
	pthread_mutex_t	*f_right;
	long			t_last_eat;
	int				nb_ate;
	pthread_t		thread;
	struct s_var	*var;
	int				death;
}	t_philo;

typedef struct s_var
{
	pthread_mutex_t	*forks;
	int				nb_philo;
	int				t_eat;
	int				t_death;
	int				t_sleep;
	int				nb_eat;
	long			start;
	t_philo			*philos;
}	t_var;

//utils
int		ft_atoi(const char *str);
void	free_all(t_var *var);
long	timer(t_var *var);
long	get_time_in_ms(void);

//routine
void	*philo_routine(void *philosophe);

//init
t_var	*init_var(t_var *var, char **argv, int argc);

#endif