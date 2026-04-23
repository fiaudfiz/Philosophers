/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:04 by miouali           #+#    #+#             */
/*   Updated: 2026/04/23 13:07:32 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    t_global_struct     *global;
    int i;
    pthread_t           tid;

    if (ac != 5 && ac != 6)
    {
        prog_usage();
        return (0);
    }
    global = malloc(sizeof(t_global_struct)); //struct de base
    if (!global)
    {
        exit_philo(global);
        return (1);
    }
    if (parse_args(ac, av, global) != 0) //parser nombres/positifs //peut etre deja les ranger
        return (write(2, "Error\n", 6));
    global->tab = malloc (sizeof(t_tab_of_thread) * global->number_of_philo); //structure du tableau des threads
    if (!global->tab)
    {
        exit_philo(global);
        return (1);
    }
    //il faut remplir le tab avec des nombres
    i = 1;
    while (i <= global->number_of_philo)
    {
        global->tab[i].number = i;
        i++;
    }
    global->fork = malloc(sizeof(pthread_mutex_t) * global->number_of_philo); //tableau des mutex
    if (!global->fork)
    {
        exit_philo(global);
        return (1);
    }
    global->fork_print = malloc(sizeof(pthread_mutex_t));
    //declaration des mutex, thread, et lancement ici
    init_variables(global, global->tab); //atoi pour transformer tous les args en number
    pthread_create(&tid, NULL, routine_body_guard, global); //thread pour surveiller;
    //ici qqun est mort on doit join les threads
    i = 1;
    while (i <= global->number_of_philo)
    {
        pthread_join(global->tab[i].tid, NULL);
        i++;
    }
    pthread_join(tid, NULL);
    //ici tout est join on peut tout detruire
    exit_philo(global);
}