/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:23:01 by miouali           #+#    #+#             */
/*   Updated: 2026/04/28 14:51:07 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine_thread(void *arg)
{
    t_tab_of_thread *tab = (t_tab_of_thread *)arg;

    tab->tid = pthread_self();//remplir le tid  
    if ((tab->ptr->number_of_philo % 2 != 0) && (tab->number == tab->ptr->number_of_philo)) //cas ou cest le dernier et on a un nombre impair
        last_odd_thread(tab);
    else if (tab->number % 2 != 0) //impair
        odd_thread(tab);
    else //pair
        even_thread(tab);
    return (NULL);
}


void *even_thread(t_tab_of_thread *tab)
{
    while (check_is_died(tab->ptr) == 0)
    {
        print_philo(tab->ptr, tab->number, 5);
        if (check_is_died(tab->ptr) != 0)
            break;
        pthread_mutex_lock(tab->fork_right);
        print_philo(tab->ptr, tab->number, 1);
        if (check_is_died(tab->ptr) != 0)
        {
            pthread_mutex_unlock(tab->fork_right);
            break;
        }
        pthread_mutex_lock(tab->fork_left);
        print_philo(tab->ptr, tab->number, 2);
        if (check_is_died(tab->ptr) != 0)
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
        pthread_mutex_lock(tab->ptr->mutex_meal);
        tab->number_of_eat += 1;
        pthread_mutex_unlock(tab->ptr->mutex_meal);
        if (check_is_died(tab->ptr) != 0)   
            break;
        print_philo(tab->ptr, tab->number, 4);
        if (check_is_died(tab->ptr) != 0)    
            break;          
        usleep(tab->ptr->time_to_sleep * 1000);
        usleep(tab->ptr->time_to_eat * 1000);
    }
    return (NULL);
}

void    *odd_thread(t_tab_of_thread *tab)
{
    while (check_is_died(tab->ptr) == 0)
    {
        if (check_is_died(tab->ptr) != 0)
            break;
        pthread_mutex_lock(tab->fork_left);
        print_philo(tab->ptr, tab->number, 2);
        pthread_mutex_lock(tab->fork_right);
        print_philo(tab->ptr, tab->number, 1);
        if (check_is_died(tab->ptr) != 0)
        {
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            break;
        }
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
        if (check_is_died(tab->ptr) != 0)
            break;
        usleep(tab->ptr->time_to_sleep * 1000);
        print_philo(tab->ptr, tab->number, 5);
        if (check_is_died(tab->ptr) != 0)
            break;
        usleep(tab->ptr->time_to_eat * 1000);
    }
    return (NULL);
}

void *last_odd_thread(t_tab_of_thread *tab)
{
    while (check_is_died(tab->ptr) == 0)
    {
        usleep(tab->ptr->time_to_eat * 1000);
        if (check_is_died(tab->ptr) != 0)
            break;
        pthread_mutex_lock(tab->fork_right);
        print_philo(tab->ptr, tab->number, 1);
        pthread_mutex_lock(tab->fork_left);
        print_philo(tab->ptr, tab->number, 2);
        if (check_is_died(tab->ptr) != 0)
        {
            pthread_mutex_unlock(tab->fork_right);
            pthread_mutex_unlock(tab->fork_left);
            break;
        }
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
        if (check_is_died(tab->ptr) != 0)
            break;
        usleep(tab->ptr->time_to_sleep * 1000);
        print_philo(tab->ptr, tab->number, 5);
        if (check_is_died(tab->ptr) != 0)
            break;
    }
    return (NULL);
}