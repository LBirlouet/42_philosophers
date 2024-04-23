/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:37 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/23 12:59:53 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

// void	print_sleep(t_data *data, int wich_philo)
// {
// 	u_int64_t time;

// 	time = get_time_ms() - data->time_start;
// 	printf("[%llu] [%d]is sleeping\n", time, wich_philo);
// 	return ;
// }

void	print(t_data *data, int id, char *msg)
{
	u_int64_t time;

	pthread_mutex_lock(&data->mutex_msg);
	time = get_time_ms() - data->time_start;
	printf("[%llu] [%d] %s\n", time, id, msg);
	pthread_mutex_unlock(&data->mutex_msg);

}