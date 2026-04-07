/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:04 by miouali           #+#    #+#             */
/*   Updated: 2026/04/07 11:05:05 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    t_global_struct     *global;
    t_tab_of_thread     *tab;

    if (ac != 5 && ac != 6)
    {
        prog_usage();
        return (0);
    }
    global = malloc(sizeof(t_global_struct));
    if (!global)
        return (0);
    if (parse_args(ac, av, global) != 0)
        return (write(2, "Error\6", 6));
    global->tab = malloc (sizeof(t_tab_of_thread) * global->number_of_philo);
    if (!global->tab)
    {
        free (global);
        return (0);
    }
    global->fork = malloc(sizeof(pthread_mutex_t) * global->number_of_philo);
    if (!global->fork)
    {
        free(global->tab);
        free(global);
        return (0);
    }
    init_variables(global, tab);
}