/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:23:01 by miouali           #+#    #+#             */
/*   Updated: 2026/04/30 11:48:23 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_thread(void *arg)
{
	t_tab_of_thread	*tab;

	tab = (t_tab_of_thread *)arg;
	tab->tid = pthread_self();
	if ((tab->ptr->number_of_philo % 2 != 0)
		&& (tab->number == tab->ptr->number_of_philo))
		last_odd_thread(tab);
	else if (tab->number % 2 != 0)
		odd_thread(tab);
	else
		even_thread(tab);
	return (NULL);
}

void	*even_thread(t_tab_of_thread *tab)
{
	while (check_is_died(tab->ptr) == 0)
	{
		print_philo(tab->ptr, tab->number, 5);
		if (check_is_died(tab->ptr) != 0)
			break ;
		usleep(tab->ptr->time_to_eat * 1000);
		if (check_is_died(tab->ptr) != 0)
			break ;
		pthread_mutex_lock(tab->fork_right);
		print_philo(tab->ptr, tab->number, 1);
		pthread_mutex_lock(tab->fork_left);
		print_philo(tab->ptr, tab->number, 2);
		if (check_is_died(tab->ptr) != 0)
		{
			pthread_mutex_unlock(tab->fork_right);
			pthread_mutex_unlock(tab->fork_left);
			break ;
		}
		eat_philo(tab);
		print_philo(tab->ptr, tab->number, 4);
		if (check_is_died(tab->ptr) != 0)
			break ;
		usleep(tab->ptr->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*odd_thread(t_tab_of_thread *tab)
{
	while (check_is_died(tab->ptr) == 0)
	{
		if (check_is_died(tab->ptr) != 0)
			break ;
		pthread_mutex_lock(tab->fork_left);
		print_philo(tab->ptr, tab->number, 2);
		pthread_mutex_lock(tab->fork_right);
		print_philo(tab->ptr, tab->number, 1);
		if (check_is_died(tab->ptr) != 0)
		{
			pthread_mutex_unlock(tab->fork_left);
			pthread_mutex_unlock(tab->fork_right);
			break ;
		}
		eat_philo(tab);
		print_philo(tab->ptr, tab->number, 4);
		if (check_is_died(tab->ptr) != 0)
			break ;
		usleep(tab->ptr->time_to_sleep * 1000);
		print_philo(tab->ptr, tab->number, 5);
		if (check_is_died(tab->ptr) != 0)
			break ;
		usleep(tab->ptr->time_to_eat * 1000);
	}
	return (NULL);
}

void	*last_odd_thread(t_tab_of_thread *tab)
{
	while (check_is_died(tab->ptr) == 0)
	{
		print_philo(tab->ptr, tab->number, 5);
		if (check_is_died(tab->ptr) != 0)
			break ;
		usleep(tab->ptr->time_to_eat * 1000);
		if (check_is_died(tab->ptr) != 0)
			break ;
		pthread_mutex_lock(tab->fork_right);
		print_philo(tab->ptr, tab->number, 1);
		pthread_mutex_lock(tab->fork_left);
		print_philo(tab->ptr, tab->number, 2);
		if (check_is_died(tab->ptr) != 0)
		{
			pthread_mutex_unlock(tab->fork_right);
			pthread_mutex_unlock(tab->fork_left);
			break ;
		}
		eat_philo(tab);
		print_philo(tab->ptr, tab->number, 4);
		if (check_is_died(tab->ptr) != 0)
			break ;
		usleep(tab->ptr->time_to_sleep * 1000);
	}
	return (NULL);
}
