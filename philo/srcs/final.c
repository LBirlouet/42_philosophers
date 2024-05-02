/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:17:55 by lbirloue          #+#    #+#             */
/*   Updated: 2024/04/29 11:18:42 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
	return (0);
}

int	destroy_mutex_init(t_data *data, int i)
{
	pthread_mutex_destroy(&data->mutex_msg);
	pthread_mutex_destroy(&data->mutex_death);
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i--;
	}
	return (-1);
}

int	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_msg);
	pthread_mutex_destroy(&data->mutex_death);
	return (0);
}

int	free_all(t_data *data)
{
	free(data->fork);
	free(data->philos);
	return (0);
}
