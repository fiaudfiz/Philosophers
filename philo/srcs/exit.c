/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:35:16 by miouali           #+#    #+#             */
/*   Updated: 2026/04/28 11:15:59 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//cette fonction est appelee apres que les threads sont arretes donc c juste du free
//detruire les mutex (mutex de print aussi)
//liberer ressources
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
    if (global)
        free(global);
    return ;
}
