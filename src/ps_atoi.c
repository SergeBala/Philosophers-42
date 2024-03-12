/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalasho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:43:00 by sbalasho          #+#    #+#             */
/*   Updated: 2023/06/07 18:43:15 by sbalasho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (s2[i]));
}

int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
	{
		return (1);
	}
	return (0);
}

long long	ps_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] && str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (message_error("Atoi: non-numeric chars!\n", -1));
	if ((number > INT_MAX && sign == 1) || (number * sign) < INT_MIN)
		return (message_error("Atoi: out of int limits!\n", -1));
	return (sign * number);
}

// int	is_a_non_neg_int_string(char *str)
// {
// 	int	i;
// 	int post_zero_flag;
// 	int	post_zero_index;

// 	i = 0;
// 	post_zero_flag = 0;
// 	post_zero_index = 0;
// 	while (str[i])
// 	{
// 		if (ft_isdigit(str[i]) && str[i] != '0' && post_zero_flag == 0)
// 		{
// 			post_zero_flag = 1;
// 			post_zero_index = i;
// 		}
// 		if (!ft_isdigit(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	if (ft_strcmp(str + post_zero_index, "2147483647") < 0)
// 		return (0);
// 	return (1);
// }
