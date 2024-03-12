/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:15:39 by sbalasho          #+#    #+#             */
/*   Updated: 2023/12/22 19:15:43 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	create_pholosophers(t_ph_data *my_data)
{
	int	i;

	i = -1;
	my_data->philosophers
		= malloc(my_data->philosopher_count * sizeof(t_philosopher));
	if (my_data->philosophers == NULL)
		return (message_error("Malloc failed\n", 1));
	while (++i < my_data->philosopher_count)
	{
		my_data->philosophers[i].id = i;
		my_data->philosophers[i].meals_eaten = 0;
		my_data->philosophers[i].last_meal_time = get_time_elapsed();
		my_data->philosophers[i].is_dead = 0;
		my_data->philosophers[i].my_data = my_data;
		my_data->philosophers[i].l_fork = &(my_data->forks[i]);
		if (my_data->philosopher_count == 1)
			my_data->philosophers[i].r_fork = NULL;
		else if (i == 0)
			my_data->philosophers[i].r_fork
				= &(my_data->forks[my_data->philosopher_count - 1]);
		else
			my_data->philosophers[i].r_fork = &(my_data->forks[i - 1]);
	}
	return (0);
}

void	cycle_check_for_stop_in_main_thread(t_ph_data *my_data)
{
	int	dead_id;

	dead_id = -1;
	while (1)
	{
		dead_id = has_death_occured(my_data);
		if (dead_id != -1 || has_everyone_eaten_n_times(my_data))
		{
			if (dead_id != -1)
				register_death(my_data, dead_id);
			else
				register_all_eaten_n_times(my_data);
			clean_up(my_data);
			break ;
		}
	}
}

int	create_philo_threads(t_ph_data *my_data)
{
	int	i;

	i = -1;
	while (++i < my_data->philosopher_count)
	{
		if (pthread_create(&(my_data->philosophers[i].thread_id),
				NULL, philo_routine, &(my_data->philosophers[i])))
		{
			destroy_all_mutexes(my_data);
			free_memory(my_data);
			return (message_error("Failed to create threads\n", 1));
		}
	}
	return (0);
}

int	main(int agrc, char **argv)
{
	t_ph_data	my_data;

	get_time_elapsed();
	if (agrc < 5 || agrc > 6)
		return (message_error("Wrong number of arguments!\n", 0));
	if (parse_the_args(&my_data, agrc, argv))
		return (1);
	if (init_all_mutexes(&my_data))
		return (1);
	if (create_pholosophers(&my_data))
		return (1);
	if (create_philo_threads(&my_data))
		return (1);
	cycle_check_for_stop_in_main_thread(&my_data);
	return (0);
}
//system("leaks philo")