/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:30:59 by miouali           #+#    #+#             */
/*   Updated: 2026/05/04 13:54:30 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     alloc_ressources(t_global_struct *global)
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
    {    
        return (1); 
    }
    global->mutex_last_meal = malloc(sizeof(pthread_mutex_t));
    if (!global->mutex_last_meal)
    {
        return (1);
    }
	global->mutex_is_died = malloc(sizeof (pthread_mutex_t));
    if (!global->mutex_is_died)
    {
        return (1);
    }
	global->mutex_meal = malloc(sizeof(pthread_mutex_t));
    if (!global->mutex_meal)
        return (1);
    return (0);
}
