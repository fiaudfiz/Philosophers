/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:35:16 by miouali           #+#    #+#             */
/*   Updated: 2026/04/29 14:13:43 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    exit_philo(t_global_struct *global)
{
    int i = 1;

    if (global->fork)
    {
        while (i <= global->number_of_philo)
        {
            pthread_mutex_destroy(&global->fork[i]);
            i++;
        }
        free(global->fork);
    }
    if (global->fork_print)
        pthread_mutex_destroy(global->fork_print);
    if (global->fork_last_meal)
        pthread_mutex_destroy(global->fork_last_meal);
    if (global->fork_is_died)
        pthread_mutex_destroy(global->fork_is_died);
    if (global->mutex_meal)
        pthread_mutex_destroy(global->mutex_meal);
    if (global->tab)
        free(global->tab);
    if (global->fork_print)
        free (global->fork_print);
    if (global->fork_last_meal)
        free (global->fork_last_meal);
    if (global->fork_is_died)
        free (global->fork_is_died);
    if (global->mutex_meal)
        free (global->mutex_meal);
    if (global)
        free(global);
    return ;
}
