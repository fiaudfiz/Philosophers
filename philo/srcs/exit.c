/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:35:16 by miouali           #+#    #+#             */
/*   Updated: 2026/04/27 19:21:48 by miouali          ###   ########.fr       */
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
    printf ("1\n");
    if (global->fork_print)
        pthread_mutex_destroy(global->fork_print);
    printf ("2\n");
    if (global->fork_last_meal)
        pthread_mutex_destroy(global->fork_last_meal);
    printf ("3\n");
    if (global->fork_is_died)
        pthread_mutex_destroy(global->fork_is_died);
    printf ("4\n");
    if (global->mutex_meal)
        pthread_mutex_destroy(global->mutex_meal);
    printf ("5\n");
    if (global->tab)
        free(global->tab);
    printf ("6\n");
    if (global)
        free(global);
    return ;
}
