#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_tab_of_thread
{
    pthread_t               tid;
    long                    time_since_last_meal;
    long                    number_of_eat;
    pthread_mutex_t         *fork_left;
    pthread_mutex_t         *fork_right;
    struct s_global_struct  *ptr;

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

#endif