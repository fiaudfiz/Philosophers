#include "philo.h"

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