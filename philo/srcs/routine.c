/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:23:01 by miouali           #+#    #+#             */
/*   Updated: 2026/04/27 10:44:58 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine_thread(void *arg)
{
    t_tab_of_thread *tab = (t_tab_of_thread *)arg;

    tab->tid = pthread_self();
    //remplir le tid
    if (tab->number % 2 != 0) //impair
    {
        while (!tab->ptr->is_died) //ajouter le max de repas
        {
            //mutex a ajouter
            if (tab->ptr->is_died != 0)
                break;
            // mutex
            pthread_mutex_lock(tab->fork_left);
            print_philo(tab->ptr, tab->number, 2);
            pthread_mutex_lock(tab->fork_right);
            print_philo(tab->ptr, tab->number, 2);
            //mutex
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->fork_right);
                break;
            }
            //mutex
            print_philo(tab->ptr, tab->number, 3);
            pthread_mutex_lock(tab->ptr->fork_last_meal);
            tab->time_since_last_meal = get_time_ms(); //fonction pour ramener un temps en micro secondes
            pthread_mutex_unlock(tab->ptr->fork_last_meal);
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            print_philo(tab->ptr, tab->number, 4);

            //mutex
            if (tab->ptr->is_died != 0)
                break;
            //mutex
            usleep(tab->ptr->time_to_sleep * 1000);
            print_philo(tab->ptr, tab->number, 5);
            //mutex
            if (tab->ptr->is_died != 0)
                 break;
            //mutex
        }
    }
    else //pair
    {
        while (!tab->ptr->is_died) //ajouter le max de repas
        {
            print_philo(tab->ptr, tab->number, 5);
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->fork_right);
            print_philo(tab->ptr, tab->number, 2);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_right);
                break;
            }
            pthread_mutex_lock(tab->fork_left);
            print_philo(tab->ptr, tab->number, 2);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_right);
                pthread_mutex_unlock(tab->fork_left);
                break;
            }
            print_philo(tab->ptr, tab->number, 3);
            pthread_mutex_lock(tab->ptr->fork_last_meal);
            tab->time_since_last_meal = get_time_ms();
            pthread_mutex_unlock(tab->ptr->fork_last_meal);
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            if (tab->ptr->is_died != 0)
                break;
            print_philo(tab->ptr, tab->number, 4);
            if (tab->ptr->is_died != 0)
                break;
            usleep(tab->ptr->time_to_sleep * 1000);
        }
    }
    return (NULL);
}

