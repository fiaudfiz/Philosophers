/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:13 by miouali           #+#    #+#             */
/*   Updated: 2026/04/09 10:13:09 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_tab_of_thread
{
    pthread_t               tid;
    long                    time_since_last_meal;
    long                    number_of_eat;
    pthread_mutex_t         *fork_left;
    pthread_mutex_t         *fork_right;
    struct s_global_struct  *ptr;
    int                     number;

}   t_tab_of_thread ;

typedef struct s_global_struct
{
    long    time_to_eat;
    long    time_to_sleep;
    long    time_to_die;
    int     max_eat;
    int     is_died;
    t_tab_of_thread    *tab;
    int     number_of_philo;
    pthread_mutex_t      *fork;
}   t_global_struct ;

void    prog_usage(void);
void    init_variables(t_global_struct *global, t_tab_of_thread *tab);
long    get_time_ms(void);

#endif