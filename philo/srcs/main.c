/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:04 by miouali           #+#    #+#             */
/*   Updated: 2026/04/08 11:02:44 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>


int main(int ac, char **av)
{
    t_global_struct     *global;
    t_tab_of_thread     *tab;
    int i = 0;
    pthread_t           tid;

    if (ac != 5 && ac != 6)
    {
        prog_usage();
        return (0);
    }
    global = malloc(sizeof(t_global_struct)); //struct de base
    if (!global)
        return (0);
    if (parse_args(ac, av, global) != 0) //parser nombres/positifs //peut etre deja les ranger
        return (write(2, "Error\n", 6));
    global->tab = malloc (sizeof(t_tab_of_thread) * global->number_of_philo); //structure du tableau des threads
    if (!global->tab)
    {
        free (global);
        return (0);
    }
    //il faut remplir le tab avec des nombres
    i = 0;
    while (i < global->number_of_philo)
    {
        global->tab[i].number = i + 1;
        i++;
    }
    global->fork = malloc(sizeof(pthread_mutex_t) * global->number_of_philo); //tableau des mutex
    if (!global->fork)
    {
        free(global->tab);
        free(global);
        return (0);
    }
    //declaration des mutex ici
    init_variables(global, tab); //init variables peut etre a bouger // peut etre declarer les mutex ici pour la place //atoi pour transformer tous les args en number
    //pk pas aussi encoyer les threads ET les mutex comme ca on init tout dedans //et aussi assigner les pointeurs de fork.
    
    
    pthread_create(tid, NULL, routine_body_guard(), global); //thread pour surveiller
    //on doit attendre que le thread body_guard envoie un signal
    while (routine_body_guard() != 1)
    {
    }
    free_and_exit(&global);
}
