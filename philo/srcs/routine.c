/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:23:01 by miouali           #+#    #+#             */
/*   Updated: 2026/04/20 15:46:59 by miouali          ###   ########.fr       */
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
            //mutex gauche
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->fork_left);
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld  %d has taken a fork\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            //mutex droit
            if (tab->ptr->is_died != 0)
            {
                //delock gauche
                pthread_mutex_unlock(tab->fork_left);
                break;
            }
            pthread_mutex_lock(tab->fork_right);
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld  %d has taken a fork\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            //manger
            if (tab->ptr->is_died != 0)
            {
                //delock les 2 mutex
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->fork_right);
                break;
            }
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld  %d is eating\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            //update last meal
            tab->time_since_last_meal = get_time_ms(); //fonction pour ramener un temps en micro secondes
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            if (tab->ptr->is_died != 0)
                break;
            //dormir
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld     %d is sleeping\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            if (tab->ptr->is_died != 0)
                break;
            usleep(tab->ptr->time_to_sleep * 1000);
            //dormir last_meal + time_to_die - time_to_eat think revenir a la boucle sans forcement dormir le mutex lock va faire attendre
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld     %d is thinking\n", get_time_ms(), tab->number);            
            pthread_mutex_unlock(tab->ptr->fork_print);
            if (tab->ptr->is_died != 0)
                break;
        }
    }
    else //pair
    {
        while (!tab->ptr->is_died) //ajouter le max de repas
        {
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld     %d is thinking\n", get_time_ms(), tab->number);            
            pthread_mutex_unlock(tab->ptr->fork_print);
            //gauche
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->fork_right);
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld  %d has taken a fork\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            //droite
            if (tab->ptr->is_died != 0)
            {
                //delock gauche
                pthread_mutex_unlock(tab->fork_right);
                break;
            }
            pthread_mutex_lock(tab->fork_left);
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld  %d has taken a fork\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            //manger
            if (tab->ptr->is_died != 0)
            {
                //delock les 2 mutex
                pthread_mutex_unlock(tab->fork_right);
                pthread_mutex_unlock(tab->fork_left);
                break;
            }
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld  %d is eating\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            //update last meal
            tab->time_since_last_meal = get_time_ms();
            usleep(tab->ptr->time_to_eat * 1000);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            if (tab->ptr->is_died != 0)
                break;
            //dormir
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->ptr->fork_print);
            printf("%ld     %d is sleeping\n", get_time_ms(), tab->number);
            pthread_mutex_unlock(tab->ptr->fork_print);
            if (tab->ptr->is_died != 0)
                break;
            usleep(tab->ptr->time_to_sleep * 1000);
        }
    }
    //normalement ici aucun mutex n'est lock donc on peut quit normalement
    //quit
    return (NULL);
}

