/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:04 by miouali           #+#    #+#             */
/*   Updated: 2026/05/05 15:58:40 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_global_struct	*global;

	if (ac != 5 && ac != 6)
	{
		prog_usage();
		return (0);
	}
	global = malloc(sizeof(t_global_struct));
	if (!global)
		return (1);
	if (parse_args(ac, av, global) != 0)
		return (write(2, "Error\n", 6));
	if (alloc_ressources(global) != 0)
	{
		exit_philo(global);
		return (1);
	}
	init_variables(global, global->tab);
	if (start_philos(global) != 0)
	{
		join_and_quit(global);
		return (1);
	}
	join_and_quit(global);
	return (0);
}
