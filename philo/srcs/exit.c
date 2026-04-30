/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:35:16 by miouali           #+#    #+#             */
/*   Updated: 2026/04/30 12:27:08 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(t_global_struct *global)
{
	int	i;

	i = 1;
	if (global->fork)
	{
		while (i <= global->number_of_philo)
		{
			pthread_mutex_destroy(&global->fork[i]);
			i++;
		}
		free(global->fork);
	}
	if (global->mutex_print)
		pthread_mutex_destroy(global->mutex_print);
	if (global->mutex_last_meal)
		pthread_mutex_destroy(global->mutex_last_meal);
	if (global->mutex_is_died)
		pthread_mutex_destroy(global->mutex_is_died);
	if (global->mutex_meal)
		pthread_mutex_destroy(global->mutex_meal);
	if (global->tab)
		free(global->tab);
	if (global->mutex_print)
		free (global->mutex_print);
	if (global->mutex_last_meal)
		free (global->mutex_last_meal);
	if (global->mutex_is_died)
		free (global->mutex_is_died);
	if (global->mutex_meal)
		free (global->mutex_meal);
	if (global)
		free(global);
	return ;
}
