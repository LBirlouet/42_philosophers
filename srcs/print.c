/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:37 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/17 12:31:30 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

void	print_sleep(t_data *data, int wich_philo)
{
	u_int64_t time;

	time = get_time_ms() - data->time_start;
	printf("[%llu] [%d]is sleeping\n", time, wich_philo);
	return ;
}

void	print_eat(t_data *data, int wich_philo)
{
	u_int64_t time;

	time = get_time_ms() - data->time_start;
	printf("[%llu] [%d] is eating\n", time, wich_philo);
	return ;
}

void	print_death(t_data *data, int wich_philo)
{
	u_int64_t time;

	time = get_time_ms() - data->time_start;
	printf("[%llu] [%d] is DEATH\n", time, wich_philo);
	return ;
}

void	print_fork(t_data *data, int wich_philo)
{
	u_int64_t time;

	time = get_time_ms() - data->time_start;
	printf("[%llu] [%d] has taken a fork\n", time, wich_philo);
	return ;
}


void	print_think(t_data *data, int wich_philo)
{
	u_int64_t time;

	time = get_time_ms() - data->time_start;
	printf("[%llu] [%d]is thinking\n", time, wich_philo);
	return ;
}