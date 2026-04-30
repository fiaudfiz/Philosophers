/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:28:27 by miouali           #+#    #+#             */
/*   Updated: 2026/04/30 12:27:08 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine_body_guard(void *arg)
{
	t_global_struct	*global;
	int				i;
	int				j;

	global = (t_global_struct *)arg;
	i = 1;
	while (i <= global->number_of_philo && check_is_died(global) == 0)
	{
		pthread_mutex_lock(global->mutex_last_meal);
		if (get_time_ms() - global->tab[i].time_since_last_meal
			> global->time_to_die)
		{
			pthread_mutex_lock(global->mutex_is_died);
			global->is_died = 1;
			pthread_mutex_unlock(global->mutex_is_died);
			pthread_mutex_lock(global->mutex_print);
			printf("%ld     %d is died\n", get_time_ms()
				- global->start, global->tab[i].number);
			pthread_mutex_unlock(global->mutex_print);
			break ;
		}
		pthread_mutex_unlock(global->mutex_last_meal);
		pthread_mutex_lock(global->mutex_meal);
		if (global->max_eat != -1)
		{
			j = 1;
			while (j < global->number_of_philo)
			{
				if (global->tab[j].number_of_eat >= global->max_eat)
					j++;
				else
					break ;
			}
			if (j == global->number_of_philo)
			{
				pthread_mutex_lock(global->mutex_is_died);
				global->is_died = 1;
				pthread_mutex_unlock(global->mutex_is_died);
				pthread_mutex_lock(global->mutex_print);
				printf("%ld     %d nombre max de repas\n", get_time_ms()
					- global->start, global->tab[i].number);
				pthread_mutex_unlock(global->mutex_print);
				pthread_mutex_unlock(global->mutex_meal);
				break ;
			}
		}
		pthread_mutex_unlock(global->mutex_meal);
		i = (i % global->number_of_philo) + 1;
		usleep(100);
	}
	return (NULL);
}
