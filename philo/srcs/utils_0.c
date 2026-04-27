/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:04:49 by miouali           #+#    #+#             */
/*   Updated: 2026/04/27 16:44:43 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*fonction qui recoit les 2 structs et doit init les mutex et les threads et aussi assigner les fork aux tab[x]*/
void    init_variables(t_global_struct *global, t_tab_of_thread *tab)
{
    int i;
    
    i = 1;
    //mutex dabord
    global->is_died = 0;
    while (i <= global->number_of_philo)
    {
        if (pthread_mutex_init(&global->fork[i], NULL) != 0)
            exit_philo(global);
        i++;
    }
    //creation du mutex de print
    if (pthread_mutex_init(global->fork_print, NULL) != 0)
        exit_philo(global);
    if (pthread_mutex_init(global->fork_last_meal, NULL) != 0)
        exit_philo(global);
    if (pthread_mutex_init(global->fork_is_died, NULL) != 0)
        exit_philo(global);
    if (global->max_eat != 0)
    {
        if (pthread_mutex_init(global->mutex_meal, NULL) != 0)
            exit_philo(global);
    }
    i = 1;
    if (!tab || !global->fork)
    {
        printf("error\n");
        exit_philo(global);
    }
    while (i <= global->number_of_philo)
    {
        tab[i].time_since_last_meal = get_time_ms();
        tab[i].number_of_eat = 0;
        tab[i].fork_left = &global->fork[i];
        if (i == global->number_of_philo)
            tab[i].fork_right = &global->fork[1];
        else
            tab[i].fork_right = &global->fork[i + 1];
        tab[i].ptr = global;
        i++;
    }
    i = 1;
    //declaration des philos (threads) boucle while les threads commencent direct apres
    global->start = get_time_ms();
    while (i <= global->number_of_philo) //declarer les impairs d'abord
    {
        if (i % 2 != 0)
        {
            if(pthread_create(&global->tab[i].tid, NULL, routine_thread, &global->tab[i]) != 0)
            {
                exit_philo(global);
            }
        }
        i++;
    }
    i = 1;
    while (i <= global->number_of_philo) //les pairs ensuite
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&global->tab[i].tid, NULL, routine_thread, &global->tab[i]) != 0)
            {
                exit_philo(global);
            }
        }
        i++;
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


void    print_philo(t_global_struct *global, int number, int mode)
{
    pthread_mutex_lock(global->fork_print);
    
    pthread_mutex_lock(global->fork_is_died);
    if (global->is_died == 1)
    {
        pthread_mutex_unlock(global->fork_print);
        pthread_mutex_unlock(global->fork_is_died);
        return ;
    }
    pthread_mutex_unlock(global->fork_is_died);
    if (mode == 1)
        printf ("%ld    %d has taken right fork\n", get_time_ms() - global->start, number);
    else if (mode == 2)
        printf ("%ld    %d has taken left fork\n",get_time_ms() - global->start, number);
    else if (mode == 3)
        printf ("%ld    %d is eating\n", get_time_ms() - global->start, number);
    else if (mode == 4)
        printf ("%ld    %d is sleeping\n", get_time_ms() - global->start, number);
    else if (mode == 5)
        printf ("%ld    %d is thinking\n", get_time_ms() - global->start, number);
    pthread_mutex_unlock(global->fork_print);
}
