/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:04 by miouali           #+#    #+#             */
/*   Updated: 2026/04/30 12:33:52 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_global_struct	*global;
	int				i;
	pthread_t		tid;

	if (ac != 5 && ac != 6)
	{
		prog_usage();
		return (0);
	}
	global = malloc(sizeof(t_global_struct));
	if (!global)
	{
		exit_philo(global);
		return (1);
	}
	if (parse_args(ac, av, global) != 0)
		return (write(2, "Error\n", 6));
	global->tab = malloc(sizeof(t_tab_of_thread)
			* (global->number_of_philo + 1));
	if (!global->tab)
	{
		exit_philo(global);
		return (1);
	}
	i = 1;
	while (i <= global->number_of_philo)
	{
		global->tab[i].number = i;
		i++;
	}
	global->fork = malloc(sizeof(pthread_mutex_t)
			* (global->number_of_philo + 1));
	if (!global->fork)
	{
		exit_philo(global);
		return (1);
	}
	global->mutex_print = malloc(sizeof(pthread_mutex_t));
	global->mutex_last_meal = malloc(sizeof(pthread_mutex_t));
	global->mutex_is_died = malloc(sizeof (pthread_mutex_t));
	if (global->max_eat != 0)
		global->mutex_meal = malloc(sizeof(pthread_mutex_t));
	init_variables(global, global->tab);
	pthread_create(&tid, NULL, routine_body_guard, global);
	i = 1;
	while (i <= global->number_of_philo)
	{
		pthread_join(global->tab[i].tid, NULL);
		i++;
	}
	pthread_join(tid, NULL);
	exit_philo(global);
	return (0);
}
