/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:04:55 by miouali           #+#    #+#             */
/*   Updated: 2026/04/29 16:14:46 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prog_usage(void)
{
	printf("Usage : ./philo number_of_philo \
		time_to_die time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat]");
	return ;
}
