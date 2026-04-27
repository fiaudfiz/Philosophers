/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:23:01 by miouali           #+#    #+#             */
/*   Updated: 2026/04/27 19:24:46 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine_thread(void *arg)
{
    t_tab_of_thread *tab = (t_tab_of_thread *)arg;

    tab->tid = pthread_self();
    //remplir le tid

    //cas ou cest le dernier et on a un nombre impair
    if ((tab->ptr->number_of_philo % 2 != 0) && (tab->number == tab->ptr->number_of_philo))
    {
        while (!tab->ptr->is_died || tab->number_of_eat != tab->ptr->max_eat) //ajouter le max de repas
        {
            usleep(tab->ptr->time_to_eat * 1000);
           pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            pthread_mutex_lock(tab->fork_right);
            print_philo(tab->ptr, tab->number, 1);
            pthread_mutex_lock(tab->fork_left);
            print_philo(tab->ptr, tab->number, 2);
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_right);
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            print_philo(tab->ptr, tab->number, 3);
            pthread_mutex_lock(tab->ptr->fork_last_meal);
            tab->time_since_last_meal = get_time_ms(); //fonction pour ramener un temps en micro secondes
            pthread_mutex_unlock(tab->ptr->fork_last_meal);
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_right);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_lock(tab->ptr->mutex_meal);
            tab->number_of_eat += 1;
            pthread_mutex_unlock(tab->ptr->mutex_meal);
            print_philo(tab->ptr, tab->number, 4);
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            usleep(tab->ptr->time_to_sleep * 1000);
            print_philo(tab->ptr, tab->number, 5);
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died); 
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
        }
    }
    else if (tab->number % 2 != 0) //impair
    {
        while (!tab->ptr->is_died || tab->number_of_eat != tab->ptr->max_eat) //ajouter le max de repas
        {
           pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            pthread_mutex_lock(tab->fork_left);
            print_philo(tab->ptr, tab->number, 2);
            pthread_mutex_lock(tab->fork_right);
            print_philo(tab->ptr, tab->number, 1);
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->fork_right);
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            print_philo(tab->ptr, tab->number, 3);
            pthread_mutex_lock(tab->ptr->fork_last_meal);
            tab->time_since_last_meal = get_time_ms(); //fonction pour ramener un temps en micro secondes
            pthread_mutex_unlock(tab->ptr->fork_last_meal);
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            pthread_mutex_lock(tab->ptr->mutex_meal);
            tab->number_of_eat += 1;
            pthread_mutex_unlock(tab->ptr->mutex_meal);
            print_philo(tab->ptr, tab->number, 4);

            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            usleep(tab->ptr->time_to_sleep * 1000);
            print_philo(tab->ptr, tab->number, 5);
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died); 
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            usleep(tab->ptr->time_to_eat * 1000);
        }
    }
    else //pair
    {
        while (!tab->ptr->is_died || tab->number_of_eat != tab->ptr->max_eat) //ajouter le max de repas
        {
            print_philo(tab->ptr, tab->number, 5);
            
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            
            pthread_mutex_lock(tab->fork_right);
            print_philo(tab->ptr, tab->number, 1);
            
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_right);
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);

            pthread_mutex_lock(tab->fork_left);
            print_philo(tab->ptr, tab->number, 2);
            
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->fork_right);
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->ptr->fork_is_died);
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            
            print_philo(tab->ptr, tab->number, 3);
            pthread_mutex_lock(tab->ptr->fork_last_meal);
            tab->time_since_last_meal = get_time_ms();
            pthread_mutex_unlock(tab->ptr->fork_last_meal);
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            pthread_mutex_lock(tab->ptr->mutex_meal);
            tab->number_of_eat += 1;
            pthread_mutex_unlock(tab->ptr->mutex_meal);
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);    
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            
            print_philo(tab->ptr, tab->number, 4);
            
            pthread_mutex_lock(tab->ptr->fork_is_died);
            if (tab->ptr->is_died != 0)
            {
                pthread_mutex_unlock(tab->ptr->fork_is_died);    
                break;
            }
            pthread_mutex_unlock(tab->ptr->fork_is_died);
            
            usleep(tab->ptr->time_to_sleep * 1000);
            usleep(tab->ptr->time_to_eat * 1000);
        }
    }
    return (NULL);
}

