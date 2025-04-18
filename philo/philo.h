/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:22:59 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/18 15:10:46 by nrontard         ###   ########.fr       */
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
	pthread_mutex_t	change_eat;
	long			t_last_eat;
	int				nb_ate;
	pthread_t		thread;
	struct s_var	*var;
}	t_philo;

typedef struct s_var
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_death;
	pthread_mutex_t	print;
	int				nb_philo;
	int				t_eat;
	int				t_death;
	int				t_sleep;
	int				nb_eat;
	int				death;
	long			start;
	t_philo			*philos;
}	t_var;

//utils
int		ft_atoi(const char *str, int utils);
long	timer(t_var *var);
long	get_time_in_ms(void);
void	destroy_mutex(t_var *var, int nb_forks);
void	sleep_ms(int duration);

//routine
void	*philo_routine(void *philosophe);
void	mutex_print(t_philo *philo, char *action);

//check
void	check_conditions(t_var *var);

//init
t_var	*init_var(t_var *var, char **argv, int argc);

#endif