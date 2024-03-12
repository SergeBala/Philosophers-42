/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:33:09 by sbalasho          #+#    #+#             */
/*   Updated: 2024/01/19 19:33:12 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// returns the id of a dead philosopher of -1
int	has_death_occured(t_ph_data *my_data)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (++i < my_data->philosopher_count)
	{
		pthread_mutex_lock(&my_data->mutex_for_last_meal_time[i]);
		check = get_time_elapsed()
			- my_data->philosophers[i].last_meal_time >= my_data->time_to_die;
		if (check)
		{
			my_data->philosophers[i].is_dead = 1;
			pthread_mutex_unlock(&my_data->mutex_for_last_meal_time[i]);
			return (i);
		}
		else
			pthread_mutex_unlock(&my_data->mutex_for_last_meal_time[i]);
	}
	return (-1);
}

void	register_death(t_ph_data *my_data, int dead_philosopher_id)
{
	pthread_mutex_lock(&my_data->death_register_mutex);
	print_log_message(get_time_elapsed(),
		&(my_data->philosophers[dead_philosopher_id]), "died");
	my_data->has_death_occured = dead_philosopher_id;
	pthread_mutex_unlock(&my_data->death_register_mutex);
}

int	has_everyone_eaten_n_times(t_ph_data *my_data)
{
	int	i;

	i = -1;
	if (my_data->meals_to_eat_count == -1)
		return (0);
	while (++i < my_data->philosopher_count)
	{
		pthread_mutex_lock(&my_data->mutex_for_meals_eaten[i]);
		if (my_data->philosophers[i].meals_eaten < my_data->meals_to_eat_count)
		{
			pthread_mutex_unlock(&my_data->mutex_for_meals_eaten[i]);
			return (0);
		}
		else
			pthread_mutex_unlock(&my_data->mutex_for_meals_eaten[i]);
	}
	return (1);
}

void	register_all_eaten_n_times(t_ph_data *my_data)
{
	pthread_mutex_lock(&my_data->eaten_n_times_mutex);
	my_data->has_everyone_eaten_n_times = 1;
	pthread_mutex_unlock(&my_data->eaten_n_times_mutex);
}
