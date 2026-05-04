/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:04:49 by miouali           #+#    #+#             */
/*   Updated: 2026/05/04 13:52:14 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_variables(t_global_struct *global, t_tab_of_thread *tab)
{
	int	i;

	i = 1;
	global->is_died = 0;
	if (global->number_of_philo % 2 != 0)
		global->time_2e_sleep = global->time_to_sleep * 1000;
	else
		global->time_2e_sleep = 1000;
	while (i <= global->number_of_philo)
	{
		if (pthread_mutex_init(&global->fork[i], NULL) != 0)
			exit_philo(global);
		i++;
	}
	if (pthread_mutex_init(global->mutex_print, NULL) != 0)
		exit_philo(global);
	if (pthread_mutex_init(global->mutex_last_meal, NULL) != 0)
		exit_philo(global);
	if (pthread_mutex_init(global->mutex_is_died, NULL) != 0)
		exit_philo(global);
	if (pthread_mutex_init(global->mutex_meal, NULL) != 0)
		exit_philo(global);
	i = 1;
	if (!tab || !global->fork)
	{
		printf("error\n");
		exit_philo(global);
	}
	while (i <= global->number_of_philo)
	{
		tab[i].time_since_last_meal = get_time_ms();
		tab[i].number_of_eat = 0;
		tab[i].fork_left = &global->fork[i];
		if (i == global->number_of_philo)
			tab[i].fork_right = &global->fork[1];
		else
			tab[i].fork_right = &global->fork[i + 1];
		tab[i].ptr = global;
		i++;
	}
	i = 1;
	global->start = get_time_ms();
	while (i <= global->number_of_philo)
	{
		if (i % 2 != 0)
		{
			if (pthread_create(&global->tab[i].tid, NULL
					, routine_thread, &global->tab[i]) != 0)
				exit_philo(global);
		}
		i++;
	}
	i = 1;
	while (i <= global->number_of_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&global->tab[i].tid, NULL
					, routine_thread, &global->tab[i]) != 0)
				exit_philo(global);
		}
		i++;
	}
}

long	get_time_ms(void)
{
	struct timeval	now;
	long			time;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time);
}

void	print_philo(t_global_struct *global, int number, int mode)
{
	pthread_mutex_lock(global->mutex_print);
	if (check_is_died(global) == 1)
	{
		pthread_mutex_unlock(global->mutex_print);
		return ;
	}
	if (mode == 1)
		printf ("%ld    %d has taken right fork\n", get_time_ms()
			- global->start, number);
	else if (mode == 2)
		printf ("%ld    %d has taken left fork\n", get_time_ms()
			- global->start, number);
	else if (mode == 3)
		printf ("%ld    %d is eating : number of eat = %ld\n", get_time_ms()
			- global->start, number, global->tab[number].number_of_eat);
	else if (mode == 4)
		printf ("%ld    %d is sleeping\n", get_time_ms()
			- global->start, number);
	else if (mode == 5)
		printf ("%ld    %d is thinking\n", get_time_ms()
			- global->start, number);
	pthread_mutex_unlock(global->mutex_print);
}

int	check_is_died(t_global_struct *global)
{
	pthread_mutex_lock(global->mutex_is_died);
	if (global->is_died == 1)
	{
		pthread_mutex_unlock(global->mutex_is_died);
		return (1);
	}
	pthread_mutex_unlock(global->mutex_is_died);
	return (0);
}

void	eat_philo(t_tab_of_thread *tab)
{
	print_philo(tab->ptr, tab->number, 3);
	pthread_mutex_lock(tab->ptr->mutex_last_meal);
	tab->time_since_last_meal = get_time_ms();
	pthread_mutex_unlock(tab->ptr->mutex_last_meal);
	usleep(tab->ptr->time_to_eat * 1000);
	pthread_mutex_unlock(tab->fork_left);
	pthread_mutex_unlock(tab->fork_right);
	pthread_mutex_lock(tab->ptr->mutex_meal);
	tab->number_of_eat += 1;
	pthread_mutex_unlock(tab->ptr->mutex_meal);
}
