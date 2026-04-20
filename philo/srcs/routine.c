/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:23:01 by miouali           #+#    #+#             */
/*   Updated: 2026/04/20 13:23:03 by miouali          ###   ########.fr       */
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
            //mutex droit
            if (tab->ptr->is_died != 0)
            {
                //delock gauche
                pthread_mutex_unlock(tab->fork_left);
                break;
            }
            pthread_mutex_lock(tab->fork_right);
            //manger
            if (tab->ptr->is_died != 0)
            {
                //delock les 2 mutex
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->fork_right);
                break;
            }
            pthread_mutex_lock(tab->ptr->fork_print);
            print("manger");
            pthread_mutex_unlock(tab->ptr->fork_print);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            if (tab->ptr->is_died != 0)
                break;
            sleep(tab->ptr->time_to_eat);
            //update last meal
            tab->time_since_last_meal = get_time_ms(); //fonction pour ramener un temps en micro secondes
            //dormir
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->ptr->fork_print);
            print("dodo");
            pthread_mutex_unlock(tab->ptr->fork_print);
            if (tab->ptr->is_died != 0)
                break;
            sleep(tab->ptr->time_to_sleep);
            //dormir last_meal + time_to_die - time_to_eat think revenir a la boucle sans forcement dormir le mutex lock va faire attendre
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->ptr->fork_print);
            print("think");
            pthread_mutex_unlock(tab->ptr->fork_print);
            if (tab->ptr->is_died != 0)
                break;
            sleep(tab->time_since_last_meal + tab->ptr->time_to_die - tab->ptr->time_to_eat); //peut etre pas oblige
        }
    }
    else //pair
    {
        while (!tab->ptr->is_died) //ajouter le max de repas
        {
            //think(dormir) last_meal + time_to_die - time_to_eat
            pthread_mutex_lock(tab->ptr->fork_print);
            print("think");
            pthread_mutex_unlock(tab->ptr->fork_print);
            //gauche
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->fork_left);
            //droite
            if (tab->ptr->is_died != 0)
            {
                //delock gauche
                pthread_mutex_unlock(tab->fork_left);
                break;
            }
            pthread_mutex_lock(tab->fork_right);
            //manger
            if (tab->ptr->is_died != 0)
            {
                //delock les 2 mutex
                pthread_mutex_unlock(tab->fork_left);
                pthread_mutex_unlock(tab->fork_right);
                break;
            }
            pthread_mutex_lock(tab->ptr->fork_print);
            print("manger");
            pthread_mutex_unlock(tab->ptr->fork_print);
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            if (tab->ptr->is_died != 0)
                break;
            sleep(tab->ptr->time_to_eat);
            //update last meal
            tab->time_since_last_meal = get_time_ms();
            //dormir
            if (tab->ptr->is_died != 0)
                break;
            pthread_mutex_lock(tab->ptr->fork_print);
            print("dodo");
            pthread_mutex_unlock(tab->ptr->fork_print);
            if (tab->ptr->is_died != 0)
                break;
            sleep(tab->ptr->time_to_sleep);
        }
    }
    //normalement ici aucun mutex n'est lock donc on peut quit normalement
    //quit
    return ;
}

