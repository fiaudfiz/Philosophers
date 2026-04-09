/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:04:49 by miouali           #+#    #+#             */
/*   Updated: 2026/04/09 14:29:51 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*fonction qui recoit les 2 structs et doit init les mutex et les threads et aussi assigner les fork aux tab[x]*/
void    init_variables(t_global_struct *global, t_tab_of_thread *tab)
{
    int i;
    
    i = 0;
    //mutex dabord
    while (i < global->number_of_philo)
    {
        if (pthread_mutex_init(&global->fork[i], NULL) != 0)
            exit(global, tab);
        i++;
    }
    i = 0;
    while (i < global->number_of_philo)
    {
        tab[i].time_since_last_meal = 0;
        tab[i].number_of_eat = 0;
        tab[i].fork_left = &global->fork[i];
        tab[i].fork_right; //i + 1 sauf le dernier
        tab[i].ptr = &global;
        i++;
    }
    i = 0;
    //declaration des philos (threads) boucle while les threads commencent direct apres
    while (i < global->number_of_philo) //declarer les impairs d'abord
    {
        if (i % 2 != 0)
        {
            if(pthread_create(&global->tab[i].tid, NULL, routine_thread, &global->tab[i]) != 0)
            {
                exit(global, tab);
            }
        }
        i++;
    }
    i = 0;
    while (i < global->number_of_philo) //les pairs ensuite
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&global->tab[i].tid, NULL, routine_thread, &global->tab[i]) != 0)
            {
                exit(global, tab);
            }
            i++;
        }
    }
}

long    get_time_ms(void)
{
    struct  timeval now;
    long    time;

    gettimeofday(&now, NULL);
    time = now.tv_sec * 1000 + now.tv_usec / 1000;
    return (time);
}