/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_guard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:28:27 by miouali           #+#    #+#             */
/*   Updated: 2026/04/09 11:28:29 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    *body_guard(void *arg)
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
                signal_death;
            }   
            i++;
        }
        sleep(0.01);
    }
}