/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:28:27 by miouali           #+#    #+#             */
/*   Updated: 2026/04/23 12:17:55 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*void    *body_guard(void *arg)
{
    t_global_struct *global = (t_global_struct *)arg;
    int i = 0;
    //boucle infinie qui va parcourir tous les threads et verifier si il y en a un qui va mourir affame
    while (1)
    {
        i = 0;
        while (i < global->number_of_philo)
        {
            if (current_time() - global->tab[i].time_since_last_meal > global->time_to_die)
            {   
                global->is_died = 1;
                break;
            }
            i++;
        }
        sleep(0.01);
    }
    //ici qqun est mort, on doit quitter les threads


}*/


void *routine_body_guard(void *arg)
{
    t_global_struct *global = (t_global_struct *)arg;
    int i = 1;

    while (i <= global->number_of_philo && global->is_died == 0)
    {
        if (get_time_ms() - global->tab[i].time_since_last_meal > global->time_to_die)
        {
            global->is_died = 1;
            pthread_mutex_lock(global->fork_print);
            printf("%ld     %d is died\n", get_time_ms(), global->tab[i].number);
            pthread_mutex_unlock(global->fork_print);
            break;
        }
        i++;
        if (i == global->number_of_philo)
            i = 1;
        usleep(100);
        //sleep 1ms
    }
    //ici des que un meurt chaque thread va s'arreter tout seul
    //on doit arreter ce thread et on retourne au main
    return (NULL);
}