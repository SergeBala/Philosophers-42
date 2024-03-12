/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:23:48 by sbalasho          #+#    #+#             */
/*   Updated: 2024/01/15 19:23:54 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*philo_routine(void *data)
{
	t_philosopher	*philosopher_data;

	philosopher_data = (t_philosopher *)data;
	if (philosopher_data->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo_take_forks(philosopher_data))
			break ;
		if (philo_eat(philosopher_data))
			break ;
		if (philo_sleep_think(philosopher_data))
			break ;
	}
	return (NULL);
}

int	philo_take_forks(t_philosopher *philosopher_data)
{
	pthread_mutex_lock(philosopher_data->l_fork);
	if (check_if_should_stop(philosopher_data))
	{
		pthread_mutex_unlock(philosopher_data->l_fork);
		return (1);
	}
	print_log_message(get_time_elapsed(), philosopher_data, "has taken a fork");
	if (check_if_should_stop(philosopher_data))
	{
		pthread_mutex_unlock(philosopher_data->l_fork);
		return (1);
	}
	if (!philosopher_data->r_fork)
		return (1);
	pthread_mutex_lock(philosopher_data->r_fork);
	if (check_if_should_stop(philosopher_data))
	{
		pthread_mutex_unlock(philosopher_data->r_fork);
		pthread_mutex_unlock(philosopher_data->l_fork);
		return (1);
	}
	print_log_message(get_time_elapsed(), philosopher_data, "has taken a fork");
	return (0);
}

int	philo_eat(t_philosopher *ph_d)
{
	pthread_mutex_lock(&ph_d->my_data->mutex_for_last_meal_time[ph_d->id]);
	if (ph_d->is_dead)
	{
		pthread_mutex_unlock(ph_d->r_fork);
		pthread_mutex_unlock(ph_d->l_fork);
		pthread_mutex_unlock
			(&ph_d->my_data->mutex_for_last_meal_time[ph_d->id]);
		return (1);
	}
	ph_d->last_meal_time = get_time_elapsed();
	pthread_mutex_unlock(&ph_d->my_data->mutex_for_last_meal_time[ph_d->id]);
	print_log_message(get_time_elapsed(), ph_d, "is eating");
	if (check_if_should_stop(ph_d))
	{
		pthread_mutex_unlock(ph_d->r_fork);
		pthread_mutex_unlock(ph_d->l_fork);
		return (1);
	}
	millisecond_usleep(ph_d->my_data->time_to_eat);
	pthread_mutex_unlock(ph_d->l_fork);
	pthread_mutex_unlock(ph_d->r_fork);
	pthread_mutex_lock(&ph_d->my_data->mutex_for_meals_eaten[ph_d->id]);
	ph_d->meals_eaten++;
	pthread_mutex_unlock(&ph_d->my_data->mutex_for_meals_eaten[ph_d->id]);
	return (check_if_should_stop(ph_d));
}

int	philo_sleep_think(t_philosopher *philosopher_data)
{
	print_log_message(get_time_elapsed(), philosopher_data, "is sleeping");
	millisecond_usleep(philosopher_data->my_data->time_to_sleep);
	if (check_if_should_stop(philosopher_data))
		return (1);
	print_log_message(get_time_elapsed(), philosopher_data, "is thinking");
	return (check_if_should_stop(philosopher_data));
}

int	check_if_should_stop(t_philosopher *philosopher_data)
{
	if (has_death_occured(philosopher_data->my_data) != -1
		|| has_everyone_eaten_n_times(philosopher_data->my_data))
		return (1);
	return (0);
}
