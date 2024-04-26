/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:47:37 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/26 15:49:14 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

void	print(t_data *data, int id, char *msg)
{
	u_int64_t time;

	pthread_mutex_lock(&data->mutex_msg);
	time = get_time_ms() - data->time_start;
	if (data->death != 1)
		printf("[%llu] \t[%d] \t%s\n", time, id, msg);
	pthread_mutex_unlock(&data->mutex_msg);
}