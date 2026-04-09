#include <philo.h>

void *routine_thread(void *arg)
{
    t_tab_of_thread *tab = (t_tab_of_thread *)arg;

    if (tab->number % 2 != 0) //impair
    {
        while (1)
        {
            //mutex gauche
            pthread_mutex_lock(tab->fork_left);
            //mutex droit
            pthread_mutex_lock(tab->fork_right);
            //manger
            //penser aux mutex pour les print
            print("manger");
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            sleep(tab->ptr->time_to_eat);
            //update last meal
            tab->time_since_last_meal = get_time_ms(); //fonction pour ramener un temps en micro secondes
            //dormir
            print("dodo");
            sleep(tab->ptr->time_to_sleep);
            //dormir last_meal + time_to_die - time_to_eat think revenir a la boucle sans forcement dormir le mutex lock va faire attendre
            print("think");
            sleep(tab->time_since_last_meal + tab->ptr->time_to_die - tab->ptr->time_to_eat); //peut etre pas oblige
        }
    }
    else //pair
    {
        while (1)
        {
            //think(dormir) last_meal + time_to_die - time_to_eat
            print("think");
            //gauche
            pthread_mutex_lock(tab->fork_left);
            //droite
            pthread_mutex_lock(tab->fork_right);
            //manger
            print("manger");
            pthread_mutex_unlock(tab->fork_left);
            pthread_mutex_unlock(tab->fork_right);
            sleep(tab->ptr->time_to_eat);
            //update last meal
            tab->time_since_last_meal = get_time_ms();
            //dormir
            print("dodo");
            sleep(tab->ptr->time_to_sleep);
        }
    }
}