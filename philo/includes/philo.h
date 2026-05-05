/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:05:13 by miouali           #+#    #+#             */
/*   Updated: 2026/05/05 17:50:57 by fiaudfiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_tab_of_thread
{
	pthread_t				tid;
	long					time_since_last_meal;
	long					number_of_eat;
	pthread_mutex_t			*fork_left;
	pthread_mutex_t			*fork_right;
	struct s_global_struct	*ptr;
	int						number;
	char					padding[8];
}	t_tab_of_thread;

typedef struct s_global_struct
{
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			start;
	long			time_2e_sleep;
	int				max_eat;
	int				is_died;
	t_tab_of_thread	*tab;
	int				number_of_philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_last_meal;
	pthread_mutex_t	*mutex_is_died;
	pthread_mutex_t	*mutex_meal;
	pthread_t		tid_body_guard;
}	t_global_struct;

void	prog_usage(void);
int		init_variables(t_global_struct *global, t_tab_of_thread *tab);
long	get_time_ms(void);
void	*routine_thread(void *arg);
void	exit_philo(t_global_struct *global);
void	*routine_body_guard(void *arg);
int		parse_args(int ac, char **av, t_global_struct *global);
void	print_philo(t_global_struct *global, int number, int mode);
int		check_is_died(t_global_struct *global);
void	*even_thread(t_tab_of_thread *tab);
void	*odd_thread(t_tab_of_thread *tab);
void	*last_odd_thread(t_tab_of_thread *tab);
void	eat_philo(t_tab_of_thread *tab);
int		alloc_ressources(t_global_struct *global);
int		init_mutex(t_global_struct *global);
int		set_variables_tab(t_global_struct *global, t_tab_of_thread *tab);
int		start_philos(t_global_struct *global);
void	join_and_quit(t_global_struct *global);

#endif
