/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:28:27 by miouali           #+#    #+#             */
/*   Updated: 2026/05/05 17:54:51 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	set_philo_death(t_global_struct *global)
{
	pthread_mutex_lock(global->mutex_is_died);
	global->is_died = 1;
	pthread_mutex_unlock(global->mutex_is_died);
}

static int	check_all_philo_max_eat(t_global_struct *global, int i)
{
	int	j;

	pthread_mutex_lock(global->mutex_meal);
	if (global->max_eat != -1)
	{
		j = 1;
		while (j <= global->number_of_philo)
		{
			if (global->tab[j].number_of_eat >= global->max_eat)
				j++;
			else
				break ;
		}
		if (j > global->number_of_philo)
		{
			set_philo_death(global);
			print_philo(global, i, 6);
			pthread_mutex_unlock(global->mutex_meal);
			return (1);
		}
	}
	pthread_mutex_unlock(global->mutex_meal);
	return (0);
}

static int	check_philo_death(t_global_struct *global, int i)
{
	pthread_mutex_lock(global->mutex_last_meal);
	if (get_time_ms() - global->tab[i].time_since_last_meal
		> global->time_to_die)
	{
		set_philo_death(global);
		pthread_mutex_lock(global->mutex_print);
		printf("%ld     %d is died\n", get_time_ms()
			- global->start, global->tab[i].number);
		pthread_mutex_unlock(global->mutex_print);
		pthread_mutex_unlock(global->mutex_last_meal);
		return (1);
	}
	pthread_mutex_unlock(global->mutex_last_meal);
	return (0);
}

void	*routine_body_guard(void *arg)
{
	t_global_struct	*global;
	int				i;

	global = (t_global_struct *)arg;
	global->tid_body_guard = pthread_self();
	i = 1;
	while (i <= global->number_of_philo && check_is_died(global) == 0)
	{
		if (check_philo_death(global, i) == 1)
			break ;
		if (check_all_philo_max_eat(global, i) == 1)
			break ;
		i = (i % global->number_of_philo) + 1;
		usleep(100);
	}
	return (NULL);
}
