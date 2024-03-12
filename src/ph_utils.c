/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:15:39 by sbalasho          #+#    #+#             */
/*   Updated: 2023/12/22 19:15:43 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	message_error(char *message, int exit_code)
{
	write(2, message, ft_strlen(message));
	return (exit_code);
}

long long	get_time_elapsed(void)
{
	struct timeval		current_time;
	static long long	prog_start_time;
	static int			has_prog_start_time_been_set;

	if (gettimeofday(&current_time, NULL) != 0)
		message_error("gettimeofday has failed", 2);
	if (!has_prog_start_time_been_set)
	{
		prog_start_time = (current_time.tv_sec
				* 1000 + current_time.tv_usec / 1000);
		has_prog_start_time_been_set = 1;
	}
	return ((current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000) - prog_start_time);
}

void	millisecond_usleep(long long time_to_sleep)
{
	long long	start_time;

	start_time = get_time_elapsed();
	while (get_time_elapsed() - start_time < time_to_sleep)
		usleep(time_to_sleep / 10);
}

void	free_memory(t_ph_data *my_data)
{
	free(my_data->philosophers);
	free(my_data->forks);
	free(my_data->mutex_for_last_meal_time);
	free(my_data->mutex_for_meals_eaten);
}
