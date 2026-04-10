#include "philo.h"

void *routine_thread(void *arg)
{
    t_tab_of_thread *tab = (t_tab_of_thread *)arg;

    tab->tid = pthread_self();
    //remplir le tid
    if (tab->number % 2 != 0) //impair
    {
        while (!tab->ptr->is_died) //ajouter le max de repas
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
        while (!tab->ptr->is_died) //ajouter le max de repas
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
    //qqun est mort donc agir ici
}

//a chaque print verifier que personne est mort

void *routine_body_guard(void *arg)
{
    t_global_struct *global = (t_global_struct *)arg;
    int i = 0;

    while (i < global->number_of_philo && global->is_died == 0)
    {
        if (now() - global->tab[i].time_since_last_meal > global->time_to_die)
        {
            global->is_died = 1;
            //mutex de print
            print ("mort");
            //mutex
            break; //peut etre plus rapide car on sort direct mais peut etre besoin de sortir aussi du while (1)
        }
        i++;
        //remettre i = 0;
        sleep(0.001);
        //sleep 1ms
    }
    //ici des que un meurt chaque thread va s'arreter tout seul
    //on doit arreter ce thread
}