/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:28:27 by miouali           #+#    #+#             */
/*   Updated: 2026/04/27 10:43:45 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *routine_body_guard(void *arg)
{
    t_global_struct *global = (t_global_struct *)arg;
    int i;

    i = 1;
    while (i <= global->number_of_philo && global->is_died == 0)
    {
        pthread_mutex_lock(global->fork_last_meal);
        if (get_time_ms() - global->tab[i].time_since_last_meal > global->time_to_die)
        {
            //mutex a ajouter
            global->is_died = 1;
            //mutex a ajouter
            
            pthread_mutex_lock(global->fork_print);
            printf("%ld     %d is died\n", get_time_ms() - global->start, global->tab[i].number);
            pthread_mutex_unlock(global->fork_print);
            break;
        }
        pthread_mutex_unlock(global->fork_last_meal);
        i = (i % global->number_of_philo) + 1;
        usleep(100);
    }
    return (NULL);
}