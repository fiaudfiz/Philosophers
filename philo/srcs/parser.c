#include "philo.h"
#include "limits.h"

int     check_digits(int ac, char **av)
{
    int     i = 0;
    int     j = 0;
    while (i < ac - 1)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' && av[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}


int parse_args(int ac, char **av, t_global_struct *global)
{
    if (check_digits(ac, av) != 0)
        return (1);
    global->number_of_philo = atoi(av[1]);
    global->time_to_die = atoi(av[2]);
    global->time_to_eat = atoi(av[3]);
    global->time_to_sleep = atoi(av[4]);
    if (av[5] != NULL)
        global->max_eat = atoi(av[5]);
    return (0); 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
}