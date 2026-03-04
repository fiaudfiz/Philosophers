#include "philo.h"

void    put_arg_in_struct(int ac, char **av, t_global_struct *global)
{

}

void    init_variables(t_global_struct *global, t_tab_of_thread *tab)
{
    int i;
    
    i = 0;
    while (i < global->number_of_philo)
    {
        tab[i].time_since_last_meal = 0;
        tab[i].number_of_eat = 0;
        tab[i].fork_left =
        tab[i].fork_right = 
        tab[i].ptr = &global;
        i++;
    }
}