/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:30:59 by miouali           #+#    #+#             */
/*   Updated: 2026/05/05 18:26:04 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_ressources(t_global_struct *global)
{
	global->tab = malloc(sizeof(t_tab_of_thread)
			* (global->number_of_philo + 1));
	if (!global->tab)
		return (1);
	global->fork = malloc(sizeof(pthread_mutex_t)
			* (global->number_of_philo + 1));
	if (!global->fork)
		return (1);
	global->mutex_print = malloc(sizeof(pthread_mutex_t));
	if (!global->mutex_print)
		return (1);
	global->mutex_last_meal = malloc(sizeof(pthread_mutex_t));
	if (!global->mutex_last_meal)
		return (1);
	global->mutex_is_died = malloc(sizeof (pthread_mutex_t));
	if (!global->mutex_is_died)
		return (1);
	global->mutex_meal = malloc(sizeof(pthread_mutex_t));
	if (!global->mutex_meal)
		return (1);
	return (0);
}

int	init_mutex(t_global_struct *global)
{
	int	i;

	i = 1;
	while (i <= global->number_of_philo)
	{
		if (pthread_mutex_init(&global->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(global->mutex_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(global->mutex_last_meal, NULL) != 0)
		return (1);
	if (pthread_mutex_init(global->mutex_is_died, NULL) != 0)
		return (1);
	if (pthread_mutex_init(global->mutex_meal, NULL) != 0)
		return (1);
	return (0);
}

int	set_variables_tab(t_global_struct *global, t_tab_of_thread *tab)
{
	int		i;

	i = 1;
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
	while (i <= global->number_of_philo)
	{
		global->tab[i].number = i;
		i++;
	}
	return (0);
}

int	start_philos(t_global_struct *global)
{
	int			i;
	pthread_t	tid;

	i = 1;
	global->start = get_time_ms();
	i = 1;
	while (i <= global->number_of_philo)
	{
		if (pthread_create(&global->tab[i].tid,
				NULL, routine_thread, &global->tab[i]) != 0)
			return (1);
		i++;
	}
	pthread_create(&tid, NULL, routine_body_guard, global);
	return (0);
}

void	join_and_quit(t_global_struct *global)
{
	int	i;

	i = 1;
	while (i <= global->number_of_philo)
	{
		pthread_join(global->tab[i].tid, NULL);
		i++;
	}
	pthread_join(global->tid_body_guard, NULL);
	exit_philo(global);
}
