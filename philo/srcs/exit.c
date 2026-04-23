/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:35:16 by miouali           #+#    #+#             */
/*   Updated: 2026/04/23 13:07:16 by miouali          ###   ########.fr       */
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
    if (global->tab)
    {
        i = 1;
        while (i <= global->number_of_philo)
        {
            free(&global->tab[i]);
            i++;
        }
        free(global->tab);
    }
    if (global)
    {
        free(global);
    }
    return ;
}