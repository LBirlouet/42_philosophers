/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:10 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/29 12:40:32 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

void	*one_philo_r(void *data)
{
	t_data	*cpdata ;

	cpdata = (t_data *)data;
	pthread_mutex_lock(&cpdata->only_one_f);
	print(data, 1, TAKE_FORK);
	pthread_mutex_unlock(&cpdata->only_one_f);
	my_sleep(cpdata, cpdata->time_to_die);
	print(data, 1, DIED);
	return (0);
}

int	one_phil(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_msg, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_death, NULL))
	{
		pthread_mutex_destroy(&data->mutex_msg);
		return (1);
	}
	if (pthread_mutex_init(&data->only_one_f, NULL))
	{
		pthread_mutex_destroy(&data->mutex_msg);
		pthread_mutex_destroy(&data->mutex_death);
		return (1);
	}
	pthread_create(&data->philos[0].thread_philo, NULL, &one_philo_r, data);
	pthread_join(data->philos[0].thread_philo, NULL);
	free(data->philos);
	pthread_mutex_destroy(&data->only_one_f);
	pthread_mutex_destroy(&data->mutex_msg);
	pthread_mutex_destroy(&data->mutex_death);
	return (0);
}
