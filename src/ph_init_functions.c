/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:01:38 by sbalasho          #+#    #+#             */
/*   Updated: 2024/01/30 19:01:43 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	parse_the_args(t_ph_data *my_data, int agrc, char **argv)
{
	my_data->philosopher_count = (int)ps_atoi(argv[1]);
	my_data->time_to_die = ps_atoi(argv[2]);
	my_data->time_to_eat = ps_atoi(argv[3]);
	my_data->time_to_sleep = ps_atoi(argv[4]);
	my_data->meals_to_eat_count = -1;
	my_data->has_death_occured = -1;
	if (agrc == 6)
		my_data->meals_to_eat_count = (int)ps_atoi(argv[5]);
	if (my_data->meals_to_eat_count <= 0 && agrc == 6)
		return (message_error("Wrong number of meals\n", 1));
	if (my_data->philosopher_count < 1 || my_data->philosopher_count > 200)
		return (message_error("Wrong number of Philosophers!\n", 1));
	if (my_data->time_to_die < 60
		|| my_data->time_to_eat < 60 || my_data->time_to_sleep < 60)
		return (message_error("Wrong time_to_do args!\n", 1));
	return (0);
}

	// printf("philosopher_count: %i\n", my_data->philosopher_count);
	// printf("time to die: %i\n", my_data->time_to_die);
	// printf("time to eat: %i\n", my_data->time_to_eat);
	// printf("time to sleep: %i\n", my_data->time_to_sleep);
	// printf("meals to have: %i\n", my_data->meals_to_eat_count);
int	init_mutex_in_arr(pthread_mutex_t *mutex_arr, int mutex_index)
{
	int	j;

	j = -1;
	if (pthread_mutex_init(&(mutex_arr[mutex_index]), NULL) != 0)
	{
		while (++j < mutex_index)
			pthread_mutex_destroy(&(mutex_arr[j]));
		free(mutex_arr);
		return (message_error("Mutex init failed\n", 1));
	}
	return (0);
}

int	allocate_the_mutex_arrs(t_ph_data *my_data)
{
	my_data->forks
		= malloc(my_data->philosopher_count * sizeof(pthread_mutex_t));
	if (my_data->forks == NULL)
		return (message_error("Malloc failed when allocating memory\n", 1));
	my_data->mutex_for_last_meal_time
		= malloc(my_data->philosopher_count * sizeof(pthread_mutex_t));
	if (my_data->mutex_for_last_meal_time == NULL)
	{
		free(my_data->forks);
		return (message_error("Malloc failed when allocating memory\n", 1));
	}
	my_data->mutex_for_meals_eaten
		= malloc(my_data->philosopher_count * sizeof(pthread_mutex_t));
	if (my_data->mutex_for_meals_eaten == NULL)
	{
		free(my_data->forks);
		free(my_data->mutex_for_last_meal_time);
		return (message_error("Malloc failed when allocating memory\n", 1));
	}
	return (0);
}

int	init_all_mutexes(t_ph_data *my_data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(my_data->printer_mutex), NULL) != 0)
		return (message_error("Mutex init failed\n", 1));
	if (pthread_mutex_init(&(my_data->death_register_mutex), NULL) != 0)
		return (message_error("Mutex init failed\n", 1));
	if (pthread_mutex_init(&(my_data->eaten_n_times_mutex), NULL) != 0)
		return (message_error("Mutex init failed\n", 1));
	if (allocate_the_mutex_arrs(my_data))
		return (1);
	while (++i < my_data->philosopher_count)
	{
		if (init_mutex_in_arr(my_data->forks, i))
			return (1);
		if (init_mutex_in_arr(my_data->mutex_for_last_meal_time, i))
			return (1);
		if (init_mutex_in_arr(my_data->mutex_for_meals_eaten, i))
			return (1);
	}
	return (0);
}

int	destroy_all_mutexes(t_ph_data *my_data)
{
	int	i;

	i = -1;
	while (++i < my_data->philosopher_count)
	{
		pthread_mutex_destroy(&(my_data->mutex_for_meals_eaten[i]));
		pthread_mutex_destroy(&(my_data->mutex_for_last_meal_time[i]));
		pthread_mutex_destroy(&(my_data->forks[i]));
	}
	pthread_mutex_destroy(&(my_data->printer_mutex));
	pthread_mutex_destroy(&(my_data->death_register_mutex));
	pthread_mutex_destroy(&(my_data->eaten_n_times_mutex));
	return (0);
}
