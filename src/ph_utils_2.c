/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:25:22 by sbalasho          #+#    #+#             */
/*   Updated: 2024/01/23 19:25:25 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	join_all_threads(t_ph_data *my_data)
{
	int	i;

	i = -1;
	while (++i < my_data->philosopher_count)
	{
		if (pthread_join(my_data->philosophers[i].thread_id, NULL) != 0)
			message_error("pthread_join failed\n", 2);
	}
}
// pthread_mutex_lock(my_data->printer_mutex);
// pthread_mutex_unlock(my_data->printer_mutex);

void	print_log_message(long long time_st, t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->my_data->printer_mutex);
	printf("%lld  Philo_%i  %s\n", time_st, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->my_data->printer_mutex);
}

void	print_simple_message(t_ph_data *my_data, char *msg)
{
	pthread_mutex_lock(&my_data->printer_mutex);
	printf("%s\n", msg);
	pthread_mutex_unlock(&my_data->printer_mutex);
}

void	clean_up(t_ph_data *my_data)
{
	join_all_threads(my_data);
	destroy_all_mutexes(my_data);
	free_memory(my_data);
}
