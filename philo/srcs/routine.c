#include <philo.h>

void *routine_thread(void *arg)
{
    t_tab_of_thread *tab = (t_tab_of_thread *)arg;

    if (tab->number % 2 != 0) //impair
    {
        //mutex gauche
        pthread_mutex_lock(tab->fork_left);
        //mutex droit
        pthread_mutex_lock(tab->fork_right);
        //manger
        print("manger");
        sleep(tab->ptr->time_to_eat);
        //update last meal
        tab->time_since_last_meal = gettimeofday()
        //dormir
        print("dodo");
        sleep(tab->ptr->time_to_sleep);
        //dormir last_meal + time_to_die - time_to_eat
        sleep(tab->time_since_last_meal + tab->ptr->time_to_die - tab->ptr->time_to_eat);
    }
    else //pair
    {
        //think(dormir) last_meal + time_to_die - time_to_eat
        //gauche
        //droite
        //manger
        //dormir
    }
}