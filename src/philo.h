/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:07:37 by sbalasho          #+#    #+#             */
/*   Updated: 2023/12/03 15:07:42 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_common_data	t_ph_data;

typedef struct s_philosoper
{
	int				id;
	int				meals_eaten;
	int				is_dead;
	long long		last_meal_time;
	pthread_t		thread_id;
	t_ph_data		*my_data;
	pthread_mutex_t	*r_fork;	
	pthread_mutex_t	*l_fork;

}				t_philosopher;

typedef struct s_common_data
{
	int				philosopher_count;
	int				meals_to_eat_count;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				has_death_occured; //store id of the dead guy
	int				has_everyone_eaten_n_times;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex_for_meals_eaten;
	pthread_mutex_t	*mutex_for_last_meal_time;
	pthread_mutex_t	printer_mutex;
	pthread_mutex_t	death_register_mutex;
	pthread_mutex_t	eaten_n_times_mutex;
	struct timeval	start;
}				t_ph_data;

long long	ps_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int a);
int			parse_the_args(t_ph_data *my_data, int agrc, char **argv);
int			message_error(char *message, int exit_code);
size_t		ft_strlen(const char *str);
int			allocate_the_mutex_arrs(t_ph_data *my_data);
int			init_all_mutexes(t_ph_data *my_data);
int			init_mutex_in_arr(pthread_mutex_t	*mutex_arr, int mutex_index);
int			destroy_all_mutexes(t_ph_data *my_data);
int			create_pholosophers(t_ph_data *my_data);
long long	get_time_elapsed(void);
void		millisecond_usleep(long long time_to_sleep);
void		free_memory(t_ph_data *my_data);
int			has_everyone_eaten_n_times(t_ph_data *my_data);
int			has_death_occured(t_ph_data *my_data);
void		register_death(t_ph_data *my_data, int dead_philosopher_id);
void		register_all_eaten_n_times(t_ph_data *my_data);
void		*philo_routine(void *data);
int			philo_take_forks(t_philosopher *philosopher_data);
int			philo_eat(t_philosopher *philosopher_data);
int			philo_sleep_think(t_philosopher *philosopher_data);
int			check_if_should_stop(t_philosopher *philosopher_data);
void		cycle_check_for_stop_in_main_thread(t_ph_data *my_data);
void		join_all_threads(t_ph_data *my_data);
void		print_log_message(long long time_st,
				t_philosopher *philo, char *msg);
void		print_simple_message(t_ph_data *my_data, char *msg);
void		clean_up(t_ph_data *my_data);

#endif
